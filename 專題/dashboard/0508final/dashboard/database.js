const mysql = require('mysql2/promise'); // 使用 promise 版本

const pool = mysql.createPool({
  // host: "192.168.51.140",
  host: "192.168.0.27",
  user: "groupuser",
  password: "group1234",
  database: "groupdb",
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0
});

module.exports = pool; // 導出連線池
