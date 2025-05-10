let decibelChart;
const maxDataPoints = 10;

const decibelData = {
  labels: [],
  datasets: [{
    label: '分貝值',
    data: [],
    borderColor: '#2f49d0',
    backgroundColor: 'rgba(47,73,208,0.1)',
    tension: 0.3,
    pointBackgroundColor: '#fff',
    pointRadius: 4
  }]
};

// 初始化 Chart.js
const ctx2 = document.getElementById('decibelLineChart').getContext('2d');
decibelChart = new Chart(ctx2, {
  type: 'line',
  data: decibelData,
  options: {
    maintainAspectRatio: false,
    responsive: true,
    plugins: {
      legend: { display: false },
      datalabels: {
        color: '#2f49d0',
        align: 'top',
        font: { weight: 'bold', size: 12 },
        formatter: value => value
      }
    },
    scales: {
      y: {
        beginAtZero: true,
        title: { display: false, text: 'dB' }
      }
    },
    layout: {
      padding: {
        top: 20,
        right: 25,
        bottom: 10,
        left: 10
      }
    }
  },
  plugins: [ChartDataLabels]
});

// 從後端取得分貝資料並更新圖表
// async function fetchNoiseData() {
//   try {
//     const response = await fetch('/api/noise');
//     const result = await response.json();

//     decibelData.labels = result.map(row => row.time);
//     decibelData.datasets[0].data = result.map(row => row.decibel);
//     decibelChart.update();
//   } catch (err) {
//     console.error('載入噪音資料失敗:', err);
//   }
// }

async function fetchNoiseData() {
  try {
    const response = await fetch('/api/noise');
    const result = await response.json();

    decibelData.labels = result.map(row => row.time);
    decibelData.datasets[0].data = result.map(row => row.decibel);

    // 標記 ALERT 狀態的顏色（紅），其他為藍
    const alertColors = result.map(row => row.status === 'ALERT' ? '#e63946' : '#2f49d0');
    const labelColors = result.map(row => row.status === 'ALERT' ? '#e63946' : '#2f49d0');

    decibelChart.data.datasets[0].pointBackgroundColor = alertColors;
    decibelChart.options.plugins.datalabels.color = labelColors;

    decibelChart.update();
  } catch (err) {
    console.error('載入噪音資料失敗:', err);
  }
}


// 每3秒更新一次
fetchNoiseData();
setInterval(fetchNoiseData, 3000);
