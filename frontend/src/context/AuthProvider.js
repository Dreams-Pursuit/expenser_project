import { createContext, useState } from "react";

const AuthContext = createContext({});


export function AuthProvider({ children }) {
    const [auth, setAuthOrg] = useState(localStorage.authObj ? JSON.parse(localStorage.authObj) : {});
    function setAuth(obj) {
        localStorage.authObj = JSON.stringify(obj);
        setAuthOrg(obj);
    }

    //StorageClear
    return (
        <AuthContext.Provider value={{auth, setAuth}}>
            { children }
        </AuthContext.Provider>
    )
};

export default AuthContext;