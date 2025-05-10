// 模擬數據更新
// setInterval(() => {
//     // 更新電子圍籬狀態
//     const hasIntruder = Math.random() > 0.9;
//     document.getElementById('fence-icon').textContent = hasIntruder ? '⚠️' : '🔒';
//     document.getElementById('fence-text').textContent = 
//         hasIntruder ? '警告：偵測到入侵者' : '安全：無人入侵';

// }, 3000); // 3秒更新一次

let lastStatus = ""; // 紀錄前一次狀態

async function fetchGeofenceData() {
    try {
        const response = await fetch('/api/geofence');
        const data = await response.json();

        const value = parseFloat(data.value);
        const status = data.status;

        if (status !== lastStatus || status === 'Danger') {
            updateFenceUI(status);
            lastStatus = status;
        }

    } catch (error) {
        console.error('獲取資料失敗：', error);
    }
}

// 更新畫面顯示
function updateFenceUI(status) {
    const icon = document.getElementById('fence-icon');
    const text = document.getElementById('fence-text');

    if (value >= 150) {
        icon.textContent = '🔓'; // Clear
        text.textContent = `安全：無人入侵`;
    } else if (value >= 30) {
        icon.textContent = '🚧'; // Warning
        text.textContent = `警告：前方有障礙物`;
    } else {
        icon.textContent = '⚠️'; // Danger
        text.textContent = `入侵警告：距離過近`;
    }
}

setInterval(fetchGeofenceData, 3000);
