import { useEffect } from "react";
import { useLocation, Navigate, Outlet } from "react-router-dom";
import useAuth from "../hooks/useAuth";

const RequireAuth = () => {
    const { auth }  = useAuth();
    const location = useLocation();
    // useEffect(() => {
    //         console.log(location);
    // })
    return (
        (auth?.username && location.pathname != "/")
        ? <Outlet/>
        : ((auth?.username)
        ? <Navigate to="/dashboard" state={{from: location}} replace={true}/>
        : <Navigate to="/login" state={{from: location}} replace={true}/>)
        
    )
}

export default RequireAuth;