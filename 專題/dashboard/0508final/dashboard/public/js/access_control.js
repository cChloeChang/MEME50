// 開關門控制 (使用 WebSocket)
async function sendCommand(cmd) {
    try {
        const response = await fetch('/api/door', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ command: cmd })
        });
        const result = await response.text();
        document.getElementById('door-status').textContent =
            cmd === 44 ? '狀態：已保持開啟' :
            cmd === 33 ? '狀態：已關閉' :
            '狀態：未知指令';
        console.log(result);
    } catch (error) {
        console.error('控制失敗:', error);
        document.getElementById('door-status').textContent = '控制指令傳送失敗';
    }
}


// 顯示刷卡紀錄
function getStatusText(status) {
    const statusMap = {
        'pass_entry': '進入',
        'pass_exit': '離開',
        'NoPass': '未授權',
        'nopass': '未授權'
    };
    return statusMap[status] || status;
}


async function loadAccessLogs() {
    try {
        const response = await fetch('/api/access-logs');
        const logs = await response.json();
        const tbody = document.getElementById('accessLogBody');
        tbody.innerHTML = logs.map(log => {
            const statusText = getStatusText(log.status);
            return `
            <tr>
                <td>${log.time}</td>
                <td>${log.card_uid}</td>
                <td class="status-${statusText}">${statusText}</td>
            </tr>
            `;
        }).join('');
        // tbody.innerHTML = logs.map(log => {
        //     const statusText = getStatusText(log.status);
        //     return `
        //     <tr>
        //         <td>${log.time}</td>
        //         <td>${log.name || '未知人員'}</td>
        //         <td>${log.department || '-'}</td>
        //         <td>${log.role || '-'}</td>
        //         <td>${log.card_uid}</td>
        //         <td class="status-${statusText}">${statusText}</td>
        //     </tr>
        //     `;
        // }).join('');
    } catch (error) {
        console.error('載入失敗:', error);
    }
}


// 每 3 秒自動更新刷卡紀錄
setInterval(() => {
    loadAccessLogs();
}, 3000);