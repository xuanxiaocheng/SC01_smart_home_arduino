<template>
    <div id="container" style="height: 400px;width: 100%;"></div>
</template>
<script>
import AMapLoader from '@amap/amap-jsapi-loader';
export default {
    setup() {
        let longitude = ''
        let latitude = ''
        if (navigator.geolocation) {
            //判断是否有这个对象
            navigator.geolocation.getCurrentPosition(function (pos) {
                longitude = pos.coords.longitude
                latitude = pos.coords.latitude
                console.log("经度：" + pos.coords.longitude +
                    "纬度：" + pos.coords.latitude)
            })
        } else {
            console.log("当前系统不支持GPS API")
        }
        AMapLoader.load({
            "key": "036b1f875340d0dc3375432760a578fd",                                          // 申请好的Web端开发者Key，首次调用 load 时必填
            "version": "1.4.15",                                // 指定要加载的 JSAPI 的版本，缺省时默认为 1.4.15
            "plugins": [],                                      // 需要使用的的插件列表，如比例尺'AMap.Scale'等
            "AMapUI": {                                         // 是否加载 AMapUI，缺省不加载
                "version": '1.1',                               // AMapUI 缺省 1.1
                "plugins": [],                                   // 需要加载的 AMapUI ui插件
            },
            "Loca": {                                            // 是否加载 Loca， 缺省不加载
                "version": '1.3.2'                              // Loca 版本，缺省 1.3.2
            },
        }).then((AMap) => {
            let amap = new AMap.Map('container', {
                zoom: 15,                                        //级别
                center: [longitude, latitude],                 //中心点坐标
                viewMode: '3D'                                   //使用3D视图
            });

            let marker = new AMap.Marker({
                position: [longitude, latitude] // 基点位置
            });
            // 地图添加标记
            amap.add(marker);
        }).catch(e => {
            console.log(e);
        })
    },
}
</script>