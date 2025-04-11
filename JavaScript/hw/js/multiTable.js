// 九九乘法表
function multiplication(){
    document.write("<table>");

    for(let i=1; i<=9; i++){
        document.write(`<tr>`);

        for(let j=2; j<=9; j++){
            console.log(`${i} * ${j} = ${i*j}`);
            //document.write(`${i} * ${j} = ${i*j}<br>`);
            document.write(`<td>${j} * ${i} = ${j*i}</td>`);
        }

        document.write(`</tr>`);
    }
    document.write(`</table>`);
    // document.write("<table><tr><td>PID</td><td>PName</td></tr></table>")
}

multiplication();