import {fileURLToPath, URL} from 'node:url'

import {defineConfig} from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
    plugins: [vue()],
    define: {
        global: {}
    },
    resolve: {
        alias: {
            mqtt: 'mqtt/dist/mqtt.js',
            process: "process/browser",
            '@': fileURLToPath(new URL('./src', import.meta.url))
        }
    }
})
