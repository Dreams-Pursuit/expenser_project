import * as React from 'react';
import ListItemButton from '@mui/material/ListItemButton';
import ListItemIcon from '@mui/material/ListItemIcon';
import ListItemText from '@mui/material/ListItemText';
import DashboardIcon from '@mui/icons-material/Dashboard';
import BarChartIcon from '@mui/icons-material/BarChart';
import AddIcon from '@mui/icons-material/Add';
import LogoutIcon from '@mui/icons-material/Logout';
import List from '@mui/material/List';
import Divider from '@mui/material/Divider';

import { useNavigate } from 'react-router-dom';

export default function Navigation() {
  const navigate = useNavigate();
  const onLogout = () => {
    localStorage.clear();
    sessionStorage.clear();
    navigate("/login", {replace: true});
  }
  
  const mainListItems = (
    <React.Fragment>
      <ListItemButton onClick={() => {
        navigate("/dashboard", {replace: true});
        }}>
        <ListItemIcon>
          <DashboardIcon />
        </ListItemIcon>
        <ListItemText primary="Dashboard" />
      </ListItemButton>
      <ListItemButton onClick={() => {
        navigate("/reports", {replace: true});
        }}>
        <ListItemIcon>
          <BarChartIcon />
        </ListItemIcon>
        <ListItemText primary="Reports" />
      </ListItemButton>
      <ListItemButton onClick={() => {
        navigate("/generate-form", {replace: true});
        }}>
        <ListItemIcon>
          <AddIcon />
        </ListItemIcon>
        <ListItemText primary="Generate form URL" />
      </ListItemButton>
    </React.Fragment>
  );
  
  const secondaryListItems = (
    <React.Fragment>
      <ListItemButton onClick={onLogout}>
        <ListItemIcon>
          <LogoutIcon />
        </ListItemIcon>
        <ListItemText primary="Logout" />
      </ListItemButton>
    </React.Fragment>
  );
  


  return (
    <List component="nav">
        {mainListItems}
        <Divider sx={{ my: 1 }} />
        {secondaryListItems}
    </List>
  )
}