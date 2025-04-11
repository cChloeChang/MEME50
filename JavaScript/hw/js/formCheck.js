// 顯示訊息_通用函數
function showMessage(element, message, success) {
    element.style.display = "inline";
    element.innerHTML = message;
    element.classList.remove(success ? "error" : "success");
    element.classList.add(success ? "success" : "error");
}

// 表單檢查_姓名
function checkName(){
    let userNameObj = document.getElementById("name");
    let sp = document.getElementById("usernamesp");
    sp.style.display = "none";

    userNameObj.addEventListener("blur", function () {
        let userNameObjVal = userNameObj.value;
        let count = 0;
        let isAllChinese = true;

        // 檢查每個字元是否在 4E00 到 9FFF 範圍
        for (let i = 0; i < userNameObjVal.length; i++) {
            let chinUni = userNameObjVal.charCodeAt(i);
            if (chinUni >= 0x4E00 && chinUni <= 0x9FFF) {
                count++;
            } else {
                isAllChinese = false;
            }
        }

        // 顯示驗證結果
        if (count >= 2 && isAllChinese) {
            showMessage(sp, "<i class='fa-regular fa-circle-check'></i> 正確", true);
        } else if (!isAllChinese) {
            showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 姓名必須全部為中文", false);
        } else {
            showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 至少需要兩個字", false);
        }
    });

    userNameObj.addEventListener("input", function () {
        sp.style.display = "none"; // 隱藏提示
    });
}

// 表單檢查_密碼
function checkPwd(){
    let thePwdObj = document.getElementById("pwd");
    let sp = document.getElementById("pwdsp");
    sp.style.display = "none";

    thePwdObj.addEventListener("blur", function () {
        let thePwdObjVal = thePwdObj.value;
        let thePwdObjValLen = thePwdObjVal.length;

        let specialch = ["[", "!", "@", "#", "$", "%", "^", "&", "*", "]"];
        let flag1 = false, flag2 = false, flag3 = false;

        if (thePwdObjVal == "") {
            showMessage(sp, "必須輸入密碼", false);
        } else if (thePwdObjValLen >= 6) {
            for (let i = 0; i < thePwdObjValLen; i++) {
                let ch = thePwdObjVal.charAt(i).toUpperCase();
                if(ch >= "A" && ch <= "Z"){
                    flag1 = true;
                }

                if (ch >= "0" && ch <= "9") {
                    flag2 = true;
                }

                for (let j = 0; j < specialch.length; j++) {
                    if (ch === specialch[j]) {
                        flag3 = true;
                    }
                }

                // 如果已經找到所有條件，提早結束迴圈
                if (flag1 && flag2 && flag3) break;
            }

            if (flag1 && flag2 && flag3) {
                showMessage(sp, "<i class='fa-regular fa-circle-check'></i> 正確", true);
            } else {
                showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 需包含英數字、特殊字元", false);
            }
        } else {
            showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 長度需超過6個字", false);
        }
    });

    thePwdObj.addEventListener("input", function () {
        sp.style.display = "none";
    });
}

// 表單檢查_日期
function checkDate(){
    let calObj = document.getElementById("calendar");
    let sp = document.getElementById("datesp");
    sp.style.display = "none";

    // function blur() {
    //     console.log("blur");
    //     sp.style.display = "inline"; // 顯示提示文字
    //     sp.innerHTML = "<i class='fa-regular fa-circle-xmark'></i> 請輸入日期";
    //     sp.classList.remove("success"); // 移除綠色樣式
    //     sp.classList.add("error"); // 添加紅色樣式
    //     return;
    // }

    calObj.addEventListener("blur", function () {
        calObj = document.getElementById("calendar");
        let calObjValue = calObj.value;
        console.log(typeof calObjValue);
        console.log(calObjValue);

        // 檢查 calObjValue 是否為空值（空字串、null、undefined 或 0 ）
        if (!calObjValue) {
            showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 請輸入日期", false);
            return;
        }

        // 驗證使用者輸入的日期
        let inputDate = new Date(calObjValue); // 將使用者輸入的字串轉為 Date 物件
        let [year, month, day] = calObjValue.split("/").map(Number);

        if (inputDate.getFullYear() === year &&
            inputDate.getMonth() + 1 === month && // 月份從 0 開始，所以要 +1
            inputDate.getDate() === day) {
            showMessage(sp, "<i class='fa-regular fa-circle-check'></i> 正確日期", true);
        } else {
            showMessage(sp, "<i class='fa-regular fa-circle-xmark'></i> 無此日期", false);
        }
    });

    calObj.addEventListener("input", function () {
        sp.style.display = "none";
    });
}

checkName(); 
checkPwd(); 
checkDate();