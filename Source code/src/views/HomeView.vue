<template>
  <main class="h-100 d-flex flex-column align-items-center justify-content-center">
    <h1>Pico Balon</h1>
    <img :src="logo" class="img-fluid">
    <input class="form-control mb-3 w-50 text-center" type="text" placeholder="Cihaz Id" v-model="clientId">
    <button type="button" class="btn btn-light w-50" @click="startConnection">Bağlan</button>
  </main>
</template>
<script setup>
import logo from "../assets/ballon.png";
import {startConnection,clientId} from "@/compasables/connect";
</script>
