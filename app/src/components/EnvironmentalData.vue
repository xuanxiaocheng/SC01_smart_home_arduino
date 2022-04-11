<template>
  <div class="title">Smart Home</div>
  <div class="circleFirst">
    <div class="circleSecond">
      <div class="circleCenter">
        <div class="symbol">
          <span style="font-size: 20px;">室内温度</span>°C
        </div>
        <div
          class="temperature"
          style="font-family: 'Lucida Console', 'Courier New', monospace;"
        >{{ temperature }}</div>
        <div class="temperature" style="font-size: 18px; top: 40%">
          室内湿度：
          <span style="font-size: 35px;">{{ humidity }}</span>%
        </div>
      </div>
    </div>
  </div>
  <div class="outDoorContainer">
    <span class="outDoorTemperature">
      <div>22</div>
      <div style="font-size: 18px;color: #acacac;">室外温度(°C)</div>
    </span>
    <span class="outDoorTemperature">
      <div>50</div>
      <div style="font-size: 18px;color: #acacac;">室外湿度(%)</div>
    </span>
  </div>
  <div class="switch">
    <div style="width:90%">
      <a-slider
        id="test"
        v-model:value="fanStatus"
        @afterChange="onAfterChange()"
        :disabled="checked"
        style="margin-bottom: 40px;"
      />
      <span style="font-size: 15px; font-weight: 600; color: #acacac; margin-right: 20px;">智能风扇调节</span>
      <a-switch v-model:checked="checked" @change="onAfterChange()" />
      <span style="font-size: 15px; font-weight: 600; color: #acacac; margin: 0 20px;">温度设定</span>
      <a-input v-model:value="wantTemperature" style="width: 50px;" :disabled="checked" />
    </div>
    <svg :class="`fanIcon ${active}`">
      <use xlink:href="#icon-fan" />
    </svg>
  </div>
  <div class="switch">
    <div style="width:90%; text-align: left">
     <a-switch v-model:checked="switchCtrl" @change="onAfterChange()"/>
     <span style="font-size: 15px; font-weight: 600; color: #acacac; margin-left: 20px;">智能开关控制</span>
    </div>
  </div>
</template>

<script>
import '../assets/icons/button_On.svg'
import '../assets/icons/fan.svg'
import { ref } from 'vue'
export default {
  name: 'HelloWorld',
  setup() {
    let active = ref('')
    let checked = ref(false)
    let switchCtrl = ref(false)
    const wantTemperature = ref('26')
    const temperature = ref('NAN')
    const humidity = ref('NaN')
    const mqtt = require("mqtt");
    const fanStatus = ref(0)
    const client = mqtt.connect('ws://47.106.219.80:7000', {
      username: "user",
      password: '123456'
    });
    let loading = ref(false)

    client.on("connect", function () {
      console.log("服务器连接成功");
      console.log(client.options.clientId);
      client.subscribe("2055479672", { qos: 1 }); // 订阅text消息
    });

    client.on("message", function (top, message) {
      temperature.value = JSON.parse(message.toString()).temperature
      humidity.value = JSON.parse(message.toString()).humidity
      fanStatus.value = parseInt(parseInt(JSON.parse(message.toString()).fanStatus - 155))
    })


    const onAfterChange = (() => {
      client.publish("2055479672-Fan", JSON.stringify({ fan: fanStatus.value == 0 ? 0 : parseInt(fanStatus.value) + 155, fanAutoCtrl: checked.value ? 1 : 0, wantTemperature: wantTemperature.value, switchStatus: switchCtrl.value ? 1 : 0}), { qos: 0, retain: true });
    })


    return {
      temperature,
      humidity,
      fanStatus,
      loading,
      active,
      checked,
      wantTemperature,
      switchCtrl,
      onAfterChange
    }

  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped lang="less">
.title {
  margin: 20px;
  font-size: 25px;
  font-weight: bold;
  /*   letter-spacing:5px; */
}
.circleFirst {
  width: 400px;
  height: 400px;
  left: 50%;
  margin-top: 50px;
  border-radius: 50%;
  position: relative;
  transform: translate(-50%, 0%);
  background-color: #d9f0fc;
  /*   background-image: linear-gradient(#D4F0FE,#B3F3FB) */
}
.circleSecond {
  width: 380px;
  height: 380px;
  left: 50%;
  top: 50%;
  border-radius: 50%;
  position: relative;
  transform: translate(-50%, -50%);
  background-image: linear-gradient(#d4f0fe, #b3f3fb);
}
.circleCenter {
  width: 320px;
  height: 320px;
  left: 50%;
  top: 50%;
  border-radius: 50%;
  position: relative;
  transform: translate(-50%, -50%);
  background-color: #f1f7fc;
}
.symbol {
  position: absolute;
  font-size: 40px;
  right: 25%;
  top: 15%;
  font-weight: bold;
  color: #aeacb3;
}
.temperature {
  font-size: 80px;
  left: 50%;
  top: 50%;
  font-weight: bolder;
  transform: translate(-50%, -50%);
  position: relative;
}
.switch {
  margin: 40px 0;
  width: 95%;
  position: relative;
  left: 50%;
  transform: translate(-50%, 0);
  height: 15vh;
  display: flex;
  align-items: center;
  border-radius: 10px;
  background-color: rgba(255, 255, 255, 0.61);
  overflow: hidden;
  padding: 20px;

  .switchIcon {
    width: 15%;
    position: relative;
    margin: 0 20px;
  }

  .fanIcon {
    position: absolute;
    right: -80px;
    opacity: 0.2;
    z-index: -1;
  }

  .active {
    animation-name: example;
    animation-duration: 4s;
    animation-iteration-count: infinite;
  }

  @keyframes example {
    from {
      transform: rotate(0deg);
    }
    to {
      transform: rotate(360deg);
    }
  }
}
.outDoorTemperature {
  font-size: 40px;
  display: inline-block;
  margin: 20px;
}

@media screen and (max-width: 960px) {
  .circleFirst {
    width: 90vw;
    height: 90vw;
  }
  .circleSecond {
    width: 88vw;
    height: 88vw;
  }
}
</style>
