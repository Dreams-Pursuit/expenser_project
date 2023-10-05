import { useLocation, Navigate, Outlet } from "react-router-dom";
import useAuth from "../hooks/useAuth";

const UnauthedOnly = () => {
    const { auth }  = useAuth();
    const location = useLocation(); 

    return (
        auth?.username
        ? <Navigate to="/dashboard" state={{from: location}} replace={true}/>
        : <Outlet />
    )
}

export default UnauthedOnly;