// 模擬員工心跳數據
const persons = [
    { name: '王小明', heart: 76, status: '正常' },
    { name: '李小華', heart: 92, status: '正常' },
    { name: '陳大同', heart: 120, status: '異常' }
];
const tbody = document.getElementById('personTableBody');
persons.forEach(p => {
    const tr = document.createElement('tr');
    tr.innerHTML = `<td>${p.name}</td><td>${p.heart}</td><td style="color:${p.status==='正常'?'#2f49d0':'#ff4d4d'}">${p.status}</td>`;
    tbody.appendChild(tr);
});