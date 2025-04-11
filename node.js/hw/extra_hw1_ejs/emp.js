const express = require('express');
const app = express();
app.listen(8181);

const fs = require('fs'); 
const csvToJson = require('convert-csv-to-json');
app.set('view engine', 'ejs');

app.use(express.urlencoded({extended: true})); // 啟用 body-parser
app.use(express.static('public'));
const file_path = "./employee.csv";
// const file_path = "../m07_file/employee.csv";

// global middleware
app.use((req, res, next) => {
    res.setHeader('Content-Type', 'text/html; charset=UTF-8');
    //json = csvToJson.fieldDelimiter(',').getJsonFromCsv("../m07_file/employee.csv");
    json = csvToJson.fieldDelimiter(',').getJsonFromCsv(file_path);
    res.setHeader('Access-Control-Allow-Origin', '*');
    next();
});

app.get('/employee/getall', (req, res) => {
    // res.render('queryall', {emps: json});
    res.send(json);
});

app.get('/employee/getone', (req, res) => {
    let empno = req.query.empno;

    for(let i=0; i<json.length; i++){
        if(json[i].empno == empno){
            emp = json[i];
            break;
        }
    }
    // res.render('queryone', {emp: emp});
    if (emp) {
        res.render('queryone', { emp: emp, status: null, message: null }); // 初始狀態無消息
    } else {
        res.render('queryone', { emp: {}, status: 'fail', message: "查無此員工" });
    }
});

// fuzzy search
app.get('/employee/search', (req, res) => {
    let sinput = req.query.searchInput.trim(); // 確保去掉前後空白

    if (!sinput) {
        return res.json([]); // 如果沒有輸入搜尋條件，回傳空陣列
    }

    const results = json.filter(emp => emp.ename.includes(sinput) || emp.deptno.includes(sinput));

    console.log(typeof results[0]);
    console.log("搜尋結果:\n", results);
    res.json(results);
    // res.send(results);
});

// update employee data
app.post('/employee/update', (req, res) => {
    let { empno, ename, hiredate, salary, deptno, title } = req.body;
    let found = false;

    for (let i = 0; i < json.length; i++) {
        if (json[i].empno === empno) {
            json[i].ename = ename;
            json[i].hiredate = hiredate;
            json[i].salary = salary;
            json[i].deptno = deptno;
            json[i].title = title;
            found = true;
            break;
        }
    }

    if (!found) {
        return res.json({ status: 'fail', message: "找不到員工資料" });
    }
    // if (!found) {
    //     return res.render('queryone', { 
    //         emp: json.find(emp => emp.empno === empno) || {}, // 傳遞當前員工資料（如果找不到則空物件）
    //         status: 'fail', 
    //         message: "找不到員工資料" 
    //     });
    // }

    // json to csv
    const header = "empno,ename,hiredate,salary,deptno,title";
    const csvContent = json.map(emp =>
        `${emp.empno},${emp.ename},${emp.hiredate},${emp.salary},${emp.deptno},${emp.title}`
    ).join("\n");

    // 將更新後的資料寫入 CSV 檔案
    // fs.writeFile(file_path, header + '\n' + csvContent, (err) => {
    //     if (err) {
    //         console.error("寫入 CSV 失敗:", err);
    //         return res.json({ status: 'fail', message: "儲存失敗，請稍後再試" });
    //     }
    //     console.log("更新成功");
    //     res.json({ status: 'success', message: "更新成功" });
    // });
    fs.writeFile(file_path, header + '\n' + csvContent, (err) => {
        if (err) {
            console.error("寫入 CSV 失敗:", err);
            return res.json({ status: 'fail', message: "儲存失敗，請稍後再試" });
        }
        console.log("更新成功");
    
        // 重新讀取最新的 JSON 數據
        json = csvToJson.fieldDelimiter(',').getJsonFromCsv(file_path);
    
        res.json({ status: 'success', message: "更新成功" });
    });
});




// delete employee data
app.post('/employee/delete', (req, res) => {
    let empno = req.body.empno;
    console.log("即將刪除", req.body);

    let result = json.filter(emps => emps.empno !== empno); // 過濾出所有 empno 不等於指定 empno 的員工資料

    // json to csv
    const header = "empno,ename,hiredate,salary,deptno,title";
    let csvContent = header + '\n';

    if (result.length > 0) {
        const rows = result.map(emps => 
            `${emps.empno},${emps.ename},${emps.hiredate},${emps.salary},${emps.deptno},${emps.title}`
        );
        csvContent += rows.join('\n'); // 加入資料行
    }
    console.log(csvContent);

    fs.writeFile(file_path, csvContent, (err) => {
        if (err) {
            console.error("寫入 CSV 失敗:", err);
            return res.json({ success: false, message: '刪除失敗，請稍後再試' });
        }
        console.log('Saved!回應:', { success: true, message: "刪除成功", empno: empno });
        // 更新 json 為最新的資料（確保後續操作使用最新的資料）
        json = csvToJson.fieldDelimiter(',').getJsonFromCsv(file_path);
        res.json({ success: true, message: "刪除成功", empno: empno }); // 回傳成功訊息和刪除的 empno
    });
});

// 到insert.ejs
app.get('/employee/insert', (req, res) => {
    res.render('insert', { status: null, message: null });
});

// insert employee data
app.post('/employee/insert', (req, res) =>{
    let { empno, ename, hiredate, salary, deptno, title } = req.body;

    // 檢查所有欄位是否填寫
    const fieldsCheck = checkAllFieldsFilled({ empno, ename, hiredate, salary, deptno, title });
    if (!fieldsCheck.isValid) { //當 isValid = false 時，!fieldsCheck.isValid 會變成 true
        return res.render('insert', { status: 'fail', message: fieldsCheck.message });
    }

    // 檢查 empno 是否是 4 位數字
    const empNoFormatCheck = checkEmpNoFormat(empno);
    if (!empNoFormatCheck.isValid) {
        return res.render('insert', { status: 'fail', message: empNoFormatCheck.message });
    }
    
    // 檢查 empno 是否已存在
    const empNoExistsCheck = checkEmpNoExists(empno, json);
    if (!empNoExistsCheck.isValid) {
        return res.render('insert', { status: 'fail', message: empNoExistsCheck.message });
    }

    // 產生 CSV 格式的新員工資料
    const csvLine = `\n${empno},${ename},${hiredate},${salary},${deptno},${title}`;

    // 加資料到 CSV
    fs.appendFile(file_path, csvLine, (err) => {
        if (err) {
            console.error("寫入 CSV 失敗:", err);
            return res.render('insert', {status: 'fail', message: '新增失敗，請稍後再試'});
        }
        res.render('insert', {status: 'success', message: '新增成功'});
    });
});

// 檢查是否所有欄位都有填寫
function checkAllFieldsFilled({ empno, ename, hiredate, salary, deptno, title }) {
    if (!empno || !ename || !hiredate || !salary || !deptno || !title) {
        return { isValid: false, message: '所有欄位皆須填寫' }; // 回傳兩個屬性。isValid:是否通過檢查
    }
    return { isValid: true };
}

// 檢查 empno 是否是 4 位數字
function checkEmpNoFormat(empno) {
    if (!empno || empno.length !== 4 || isNaN(empno)) {
        return { isValid: false, message: '員工編號必須是 4 位數字' };
    }
    return { isValid: true };
}

// 檢查 empno 是否已存在
function checkEmpNoExists(empno, json) {
    let exists = false;
    // let exists = json.some(emp => emp.empno === empno); // 意思相同但超簡便寫法 .some() 會檢查陣列內是否至少有一個元素符合條件，如果有回傳 true，否則 false
    for (let emp of json) { // for...of:遍歷陣列中的每個元素
        if (emp.empno === empno) {
            exists = true;
            break;
        }
    }
    if (exists) {
        return { isValid: false, message: `員工編號 ${empno} 已存在` };
    }
    return { isValid: true };
}