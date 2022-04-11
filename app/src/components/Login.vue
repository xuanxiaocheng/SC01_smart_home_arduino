<template>
    <div>
        <svg style="margin-top: 20%;">
            <use xlink:href="#icon-logo" />
        </svg>
        <div style="font-size: 18px; font-weight: 600;">智能家居环境系统</div>
        <a-input class="input" placeholder="账号" />
        <a-input class="input" placeholder="密码" />
         <a-button style="width: 200px" type="primary">登录</a-button>
    </div>
</template>

<script>
import '../assets/icons/logo.svg'
export default {
    name: 'Login',
    setup() {

    }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped lang="less">
.input{
    width: 50%;
    display: block;
    position: relative;
    left: 50%;
    transform: translateX(-50%);
    margin:20px 0;
}
</style>
