import { createApp } from 'vue'
import App from './App.vue'
import router from './router'

import './assets/main.css'
import "bootstrap"
import "bootstrap/dist/css/bootstrap.min.css"

import "primevue/resources/themes/lara-light-blue/theme.css";
import "primevue/resources/primevue.min.css";
import 'primeicons/primeicons.css';

import PrimeVue from 'primevue/config';

import Button from 'primevue/button';


const app = createApp(App)

app.use(router)

app.use(PrimeVue);


app.component("Button",Button)


app.mount('#app')
