const fs = require('fs');
const { exec } = require('child_process');
const FIFO_PATH = '/tmp/smart_lock_fifo';
const pool = require('./database');

// 啟動 FIFO 前先建立
function createFIFOIfNeeded() {
  exec(`mkfifo ${FIFO_PATH}`, (err) => {
    if (err && err.code !== 1) {
      console.error('FIFO初始化失敗:', err);
      process.exit(1);
    } else {
      openFIFO();
    }
  });
}

let fifoStream;
function openFIFO() {
  fifoStream = fs.createWriteStream(FIFO_PATH, { flags: 'w' });

  fifoStream.on('error', (err) => {
    console.error('FIFO開啟失敗:', err);
    process.exit(1);
  });

  fifoStream.on('open', () => {
    console.log('FIFO 開啟成功');
  });
}

createFIFOIfNeeded(); // 啟動時先建立 FIFO 並開啟

// 關閉 FIFO
process.on('SIGINT', () => {
  console.log('關閉 FIFO...');
  if (fifoStream) {
    fifoStream.end(() => {
      console.log('FIFO已關閉');
      process.exit();
    });
  } else {
    process.exit();
  }
});

exports.doorControl = (req, res) => {
  const cmd = req.body.command;
  const data = cmd.toString();

  if (!fifoStream) {
    console.error('FIFO尚未開啟');
    return res.status(500).send('控制失敗');
  }

  fifoStream.write(data, (err) => {
    if (err) {
      console.error('FIFO寫入失敗:', err);
      return res.status(500).send('控制失敗');
    }
    res.send(`指令 ${data} 已發送`);
  });
};

exports.getAccessLogs = async (req, res) => {
  let conn;
  try {
    conn = await pool.getConnection();
    const [rows] = await conn.query(`
      SELECT DATE_FORMAT(timestamp, '%Y-%m-%d %H:%i:%s') AS time,
             value AS card_uid,
             status
        FROM sensor_data
       WHERE device_id = 'rfid'
       ORDER BY timestamp DESC
       LIMIT 50
    `);
    res.json(rows);
  } catch (err) {
    console.error('取得刷卡紀錄失敗:', err);
    res.status(500).send('伺服器錯誤');
  } finally {
    if (conn) conn.release();
  }
};

// exports.getAccessLogs = async (req, res) => {
//   let conn;
//   try {
//     conn = await pool.getConnection();
//     const [rows] = await conn.query(`
//       SELECT 
//         DATE_FORMAT(s.timestamp, '%Y-%m-%d %H:%i:%s') AS time,
//         s.value AS card_uid,
//         COALESCE(u.name, '未知人員') AS name,
//         COALESCE(u.department, '無部門') AS department,
//         COALESCE(u.role, '無職稱') AS role,
//         s.status
//       FROM sensor_data s
//       LEFT JOIN users u ON s.value = u.uid
//       WHERE s.device_id = 'rfid'
//       ORDER BY s.timestamp DESC
//       LIMIT 50
//     `);
//     res.json(rows);
//   } catch (err) {
//     console.error('取得刷卡紀錄失敗:', err);
//     res.status(500).send('伺服器錯誤');
//   } finally {
//     if (conn) conn.release();
//   }
// };


exports.getNoiseData = async (req, res) => {
  try {
    const [rows] = await pool.query(`
      SELECT value AS decibel, DATE_FORMAT(timestamp, '%H:%i:%s') AS time
      FROM sensor_data
      WHERE device_id = 'sensor_noise_001'
      ORDER BY timestamp DESC
      LIMIT 10
    `);
    res.json(rows.reverse()); // 最新的在後面，圖表會由左至右顯示
  } catch (err) {
    console.error('取得噪音資料失敗:', err);
    res.status(500).send('伺服器錯誤');
  }
};


exports.getGeofenceStatus = async (req, res) => {
  try {
    const [rows] = await pool.query(`
      SELECT value, status
      FROM sensor_data
      WHERE device_id = 'geofence_sensor_001'
      ORDER BY timestamp DESC
      LIMIT 1
    `);

    if (rows.length === 0) {
      return res.status(404).json({ message: '找不到資料' });
    }

    res.json(rows[0]); // { value: 12.5, status: "Warning" }
  } catch (err) {
    console.error('取得電子圍籬狀態失敗:', err);
    res.status(500).send('伺服器錯誤');
  }
};
