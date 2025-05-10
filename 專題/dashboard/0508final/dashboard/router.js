const express = require('express');
const router = express.Router();
const controller = require('./controller');

// API路由
router.post('/api/door', controller.doorControl); // 開關門
router.get('/api/access-logs', controller.getAccessLogs); // 刷卡紀錄
router.get('/api/noise', controller.getNoiseData);    // 噪音資料
router.get('/api/geofence', controller.getGeofenceStatus); // 電子圍籬


// 前端路由
router.get('*all', (req, res) => {
    res.sendFile('index.html', { root: './public' });
});

module.exports = router;
