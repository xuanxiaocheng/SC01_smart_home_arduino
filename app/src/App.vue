<template>
<div id="app">
    <router-view />
  </div>
</template>

<script>
export default {
  name: 'App',
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  width: 500px;
  background-color: #f9f9f9;
}
body {
  margin: 0;
  display: flex;
  justify-content: center;
  background-color: #f1f1f1;
}

html {
  height: auto;
}

@media screen and (max-width: 960px) {
  #app {
    width: 100vw;
  }

  body {
    width: 100vw;
  }
}
</style>
