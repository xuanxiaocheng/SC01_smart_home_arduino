import { createApp } from 'vue'
import { createRouter, createWebHistory } from 'vue-router'
import { Slider, Switch, Input, Button } from 'ant-design-vue';
import 'ant-design-vue/dist/antd.css'
import App from './App'
import Home from './components/EnvironmentalData.vue'
import Login from './components/Login.vue'

const routes = [
    { path: '/', component: Home },
    { path: '/login', component: Login },
]

const router = createRouter({
    history: createWebHistory(),
    routes,
})

const app = createApp(App);
app.use(router)
app.use(Slider)
app.use(Input)
app.use(Button)
app.use(Switch).mount('#app');