import SignIn from "./components/SignIn";
import SignUp from "./components/SignUp";
import RequireAuth from "./components/RequireAuth";
import Dashboard from "./components/dashboard/Dashboard";
import './styles/App.css';
import Error from './components/ErrorPage';

import { createBrowserRouter, RouterProvider } from "react-router-dom";



const router = createBrowserRouter([
  {
    path: "/",
    element: <RequireAuth />,
    children: [
      {
        path: "dashboard",
        element: <Dashboard />
      }
    ],
    errorElement: <Error/>
  }, 
  {
    path: "/login",
    element: <SignIn />
  },
  {
    path: "/singup",
    element: <SignUp />
  }
])
function App() {
  return (
    <> 
      <RouterProvider router={router} />
    </>
  );
}

export default App;
