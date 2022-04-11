<template>
  <div class="loading">
    <div class="dotContainer">
      <div class="dot first"></div>
      <div class="dot second"></div>
      <div class="dot third"></div>
      <div class="dot four"></div>
    </div>
  </div>
</template>

<style lang="less" scoped>
.loading {
  display: flex;
  align-items: center;
  justify-content: center;
  .dotContainer {
    width: 30px;
    height: 30px;
    position: relative;
    animation: rotate 2s infinite;
    .dot {
      width: 15px;
      height: 15px;
      border-radius: 100%;
      position: absolute;
    }
    .first {
      top: 0;
      left: 0;
      background: rgb(216, 80, 80);
    }
    .second {
      top: 0;
      left: 50%;
      background: rgb(80, 123, 216);
    }
    .third {
      top: 50%;
      left: 50%;
            background: rgb(80, 216, 171);
    }
    .four {
      left: 0%;
            background: rgb(175, 216, 80);
      top: 50%;
    }
    @keyframes rotate {
      0% {
        transform: rotate(0deg);
      }
      25% {
        transform: rotate(90deg);
      }
      50% {
        transform: rotate(180deg);
      }
      75% {
        transform: rotate(270deg);
      }
      100% {
        transform: rotate(360deg);
      }
    }
  }
}
</style>
