import axios from 'axios';

const BASE_URL = "http://localhost:18080/";

export default axios.create({
    baseURL: BASE_URL
});


export const axiosPrivate = axios.create({
    baseURL: BASE_URL,
    headers: {
        'Accept': '*/*',
        'Content-Type': 'text/plain'
    }
});