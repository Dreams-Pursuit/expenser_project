import { useEffect } from "react"; 
import axios, { axiosPrivate } from "../api/axios"
import useAuth from "./useAuth";

export default function useAxiosPrivate() {
    const { auth } = useAuth();

    useEffect(() => {
        const requestIntercept = axiosPrivate.interceptors.request.use((config) => {
            if (!config.headers['Authorization']) {
                // config.headers['Authorization'] = `Bearer ${auth.access_token}`
                console.log(config.data);
                config.data = {};
                config.data.userId = `${auth.userId}`;
                config.data.acccess_token =`${auth.acccess_token}`;
                console.log(config.data);
            }
            return config;
        }, (err) => Promise.reject(err));


        //TO DO: Navigate to the login page when refresh was unsuccessful
        const responseIntercept = axiosPrivate.interceptors.response.use(
            response => response, 
            (error) => {
                const prevRequest = error?.config;
                if (error?.response?.status === 403 & !prevRequest?.sent) {
                    prevRequest.sent = true;
                    // const newAccessToken = new refresh(); // To be finished on the server side
                    // prevRequest.headers['Authorization'] = `Bearer ${newAccessToken}`;
                    return axiosPrivate(prevRequest);
                }
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