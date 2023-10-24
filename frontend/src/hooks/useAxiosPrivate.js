import { useEffect } from "react"; 
import axios, { axiosPrivate } from "../api/axios"
import useAuth from "./useAuth";
import { BASE_URL_FRONT } from "../constants";

export default function useAxiosPrivate() {
    const { auth, setAuth } = useAuth();

    useEffect(() => {
        const requestIntercept = axiosPrivate.interceptors.request.use((config) => {
            if (!config.headers['Authorization']) {
                
                config.data = {
                    username: `${auth.username}`,
                    user_id: `${auth.userId}`
                };
                console.log(config.data);
                console.log(auth.access_token);
                config.headers['Authorization'] =`Bearer ${auth.access_token}`;
                console.log(config.headers['Authorization']);
            }
            return config;
        }, (err) => Promise.reject(err));


        //TO DO: Navigate to the login page when refresh was unsuccessful
        const responseIntercept = axiosPrivate.interceptors.response.use(
            response => response, 
            (error) => {
                const prevRequest = error?.config;
                if (error?.response?.status === 403) {
                    setAuth({});
                    alert("403. Invalid key");
                    window.location.href = BASE_URL_FRONT;
                }
                // if (error?.response?.status === 403 & !prevRequest?.sent) {
                //     prevRequest.sent = true;
                //     // const newAccessToken = new refresh(); // To be finished on the server side
                //     // prevRequest.headers['Authorization'] = `Bearer ${newAccessToken}`;
                    
                //     return axiosPrivate(prevRequest);
                // }
                return Promise.reject(error);
            }
        )

        return () => {
            axiosPrivate.interceptors.request.eject(requestIntercept);
            axiosPrivate.interceptors.response.eject(responseIntercept);
        }

    }, [auth]);

    return axiosPrivate;
}