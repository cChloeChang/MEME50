// 模擬數據更新
setInterval(() => {
    // 溫溼度
    const temp = (Math.random() * 10 + 20).toFixed(1);   // 20~30°C
    const humi = (Math.random() * 30 + 50).toFixed(1);   // 50~80%
    document.getElementById('temperature').textContent = temp;
    document.getElementById('humidity').textContent = humi;
}, 3000); // 3秒更新一次