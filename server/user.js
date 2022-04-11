/* eslint-disable no-unused-vars */
var models = require('./db')
var express = require('express')
var router = express.Router()
var mysql = require('mysql')

var conn = mysql.createConnection(models.mysql)

conn.connect()
var jsonWrite = function(res, ret) {
    if (typeof ret === 'undefined') {
        res.json('err')
    } else {
        console.log(ret)
        res.json(ret)
    }
}


// 验证管理员
router.post('/getmanage', (req, res) => {
    const sql = 'select * from manage WHERE username = ? AND password = ?'
    const params = req.body
    console.log(params)
    conn.query(sql, [params.username, params.password], function(err, result) {
            if (err) {
                console.log('验证失败' + err)
            }
            if (result) const token = $jwt.sign({
                name: params.username
            }, 'starpavilion', {
                expiresIn: 1800 // 秒到期时间
            })
            jsonWrite(res, { result, token })
        }
    })
})