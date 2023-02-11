import mqtt from "mqtt";
import {reactive, ref} from "vue";

import router from "../router/index"


const clientId = ref("");
const mqttConnect =ref() ;
const getImage = ref();
const sensor = reactive({
    c: '55',
    h: '77'
})


const startConnection = () => {
    const connectUrl = "ws://test.mosquitto.org:8081/";
    mqttConnect.value = mqtt.connect(connectUrl, {
        clientId: clientId,
        path: "/mqtt",
        protocolId: "MQTT", 
        keepalive:30,
        clean: true,
        connectTimeout: 4000,
        rejectUnauthorized: false
    });

    
    mqttConnect.value.on("connect", () => {
        console.log("bağlantı başarılı");
        mqttConnect.value.subscribe("qq1122/" + clientId.value + "/cam")
        mqttConnect.value.subscribe("qq1122/" + clientId.value + "/sensor")
        console.log(clientId)
        console.log("subscribed")
    })

    mqttConnect.value.on("error", () => {
        console.log("bağlantı başarısız");
    })

    mqttConnect.value.on("message", (topic, message) => {
        console.log("mesaj gelen topic: " + topic );
        if (topic === "qq1122/" + clientId.value + "/cam") {
            getImage.value ="data:image/jpeg;base64," + message;
        } else if (topic === "qq1122/" + clientId.value + "/sensor") {
            const data = message.toString().split(" ");
            sensor.c = data[0];
            sensor.h = data[1];
        }
    })
    router.push("/1")
}

const publish = (topic, message) => {
    mqttConnect.value.publish(topic, message);
}

export {startConnection, mqttConnect ,clientId, sensor, getImage};