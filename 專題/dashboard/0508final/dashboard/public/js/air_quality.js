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
                //grid: { color: '#333' }, //深色格線
                grid: { color: '#e0e0e0'},
                ticks: { color: '#888' }
            },
            x: {
                //grid: { color: '#333' }, //深色格線
                grid: { color: '#e0e0e0'},
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

// 模擬數據更新
setInterval(() => {
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