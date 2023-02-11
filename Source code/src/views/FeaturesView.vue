<template>

    <article class="h-100 d-flex align-items-center justify-content-center text-center">

        <div class="container-fluid">
            <div class="row">
                <div class="col-md-3">
                    <div class="d-flex align-items-center justify-content-center">
                        <img :src="celsiusImg" style="height: 100px; width:100px">
                        <Button icon="pi pi-percentage" :label="sensor.c"
                            class="p-button-rounded p-button-secondary p-button-outlined text-white" />
                    </div>
                </div>
                <div class="col-md-6">
                    <div class="d-flex align-items-center justify-content-center flex-column">
                        <img :src="getImage" style="height: 300px">
                        <Button icon="pi pi-camera" label="Fotoğraf Çek" @click="capFoto"
                            class="p-button-outlined p-button-primary text-white mt-3 fs-2 w-50" />
                    </div>
                </div>
                <div class="col-md-3">

                    <div class="d-flex align-items-center justify-content-center">
                        <img :src="humidityImg" style="height: 100px; width:100px">
                        <Button icon="pi pi-percentage" :label="sensor.h"
                            class="p-button-rounded p-button-secondary p-button-outlined text-white" />
                    </div>
                </div>
            </div>
        </div>

    </article>

</template>

<script setup>
import { ref } from "vue";
import celsiusImg from "../assets/celsius.png"
import humidityImg from "../assets/humidity.png"
import {mqttConnect, getImage,clientId, sensor} from "@/compasables/connect";

const capFoto = () => {
    mqttConnect.value.publish("qq1122/" + clientId.value + "/cam_get","takepicture");
}


</script>