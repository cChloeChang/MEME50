document.addEventListener('DOMContentLoaded', async () => {
    // 初始化 Chart.js
    const ctx = document.getElementById('airQualityChart').getContext('2d');
    const chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: Array.from({length: 10}, (_, i) => `T-${10-i}`),
            datasets: [{
                label: '一氧化碳 (CO)',
                data: [0.8, 0.9, 1.1, 1.0, 0.8, 0.7, 0.6, 0.7, 0.8, 0.9],
                borderColor: '#ff6384',
                tension: 0.4
            },{
                label: '有機揮發物 (VOC)',
                data: [2.1, 2.0, 1.8, 1.9, 2.2, 2.3, 2.1, 2.0, 1.9, 2.0],
                borderColor: '#36a2eb',
                tension: 0.4
            },{
                label: '氧氣 (O2)',
                data: [20.5, 20.6, 20.7, 20.6, 20.5, 20.4, 20.5, 20.6, 20.7, 20.8],
                borderColor: '#4bc0c0',
                tension: 0.4
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            scales: {
                y: {
                    beginAtZero: true,
                    grid: { color: '#333' },
                    ticks: { color: '#888' }
                },
                x: {
                    grid: { color: '#333' },
                    ticks: { color: '#888' }
                }
            },
            plugins: {
                legend: {
                    labels: { color: '#fff' }
                }
            }
        }
    });

    // 門控制功能
    document.getElementById('open-door').addEventListener('click', () => {
        document.getElementById('door-status').textContent = '狀態：開啟';
    });

    document.getElementById('close-door').addEventListener('click', () => {
        document.getElementById('door-status').textContent = '狀態：關閉';
    });

    // 模擬數據更新
    setInterval(() => {
        // 更新分貝值
        const decibel = Math.floor(Math.random() * 40 + 60);
        document.getElementById('decibel-value').textContent = `${decibel} dB`;
        document.getElementById('decibel-bar').style.width = `${(decibel/100)*100}%`;

        // 溫溼度
        const temp = (Math.random() * 10 + 20).toFixed(1);   // 20~30°C
        const humi = (Math.random() * 30 + 50).toFixed(1);   // 50~80%
        document.getElementById('temperature').textContent = temp;
        document.getElementById('humidity').textContent = humi;

        // 更新電子圍籬狀態
        const hasIntruder = Math.random() > 0.9;
        document.getElementById('fence-icon').textContent = hasIntruder ? '⚠️' : '🔒';
        document.getElementById('fence-text').textContent = 
            hasIntruder ? '警告：偵測到入侵者' : '安全：無人入侵';

        // 更新空氣品質
        const quality = Math.floor(Math.random() * 30 + 70);
        updateAirQuality(quality);
    }, 3000); // 3秒更新一次

    function updateAirQuality(percent) {
        document.getElementById('gauge-value').textContent = `${percent}%`;
        
        let face = '😊', label = '非常好';
        if (percent > 90) {
            face = '😊'; label = '非常好';
        } else if (percent > 80) {
            face = '🙂'; label = '良好';
        } else if (percent > 70) {
            face = '😐'; label = '一般';
        } else {
            face = '😟'; label = '較差';
        }
        
        document.getElementById('gauge-face').textContent = face;
        document.getElementById('gauge-label').textContent = label;
    }

    document.getElementById('sidebarToggle').addEventListener('click', function() {
        document.querySelector('.sidebar').classList.toggle('open');
    });
});