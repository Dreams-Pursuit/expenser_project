import { DatePicker } from '@mui/x-date-pickers/DatePicker';
import * as React from "react";
import Avatar from "@mui/material/Avatar";
import Button from "@mui/material/Button";
import CssBaseline from "@mui/material/CssBaseline";
import TextField from "@mui/material/TextField";
import FormControl from "@mui/material/FormControl";
import FormControlLabel from "@mui/material/FormControlLabel";
import Checkbox from "@mui/material/Checkbox";
import Link from "@mui/material/Link";

import InputLabel from "@mui/material/InputLabel";
import Select from "@mui/material/Select";
import MenuItem from "@mui/material/MenuItem";
import Grid from "@mui/material/Grid";
import Box from "@mui/material/Box";
import Typography from "@mui/material/Typography";
import Container from "@mui/material/Container";
import PaymentsIcon from '@mui/icons-material/Payments';


import Copyright from "../Copyright";
import CATEGORIES from "../../data/categories";
import CURRENCY_LIST from "../../data/currencyList";
import dayjs from 'dayjs';
import { useParams } from 'react-router-dom';
import axios from "../../api/axios"
import useAuth from '../../hooks/useAuth';
// import useAuth from '../hooks/useAuth';
// import { useNavigate, useLocation } from "react-router-dom";
// import axios from "../api/axios";

// function formatDate(date) {
//   console.log(date.format("YYYY-MM-DD HH:mm:ss"));
//   console.log(dayjs().format("HH:mm:ss"));
// }

export default function AddExpenseForm() {
  const { id, token } = useParams();
  const { auth, setAuth } = useAuth();
  // const axiosPrivate = useAxiosPrivate()


  const [category, setCategory] = React.useState("None");
  const [currency, setCurrency] = React.useState("UAH");
  const [date, setDate] = React.useState(dayjs())
  // const [update, setUpdate] = React.useState


  async function handleSubmit(event) {
    event.preventDefault();
    
    const formedData = new FormData(event.currentTarget);
    console.log("User id from the url");
    console.log(id);

    const data = { 
      user_id: id,
      amount: formedData.get("amount"),
      category: category,
      description: formedData.get("description"),
      date: date.format("YYYY-MM-DD HH:mm:ss"),
      currency: currency
    }
    if (!data.amount) { 
      alert("Enter the amount!");
      return;
    }
    console.log(data);
    console.log("Received token - " + token);

    try {
      const response = await axios.post('/user/transactions/add', data, {
        headers: {
          Authorization: `Bearer ${token}`
        },

      });
      console.log(response);
      alert("Your expense was added");
    } catch (err) {
      alert("Submit Error");
      console.log(err);
    }

  }

  return (
    <React.Fragment>
      <Container component="main" maxWidth="xs">
        <CssBaseline />
        <Box
          sx={{
            marginTop: 8,
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
          }}
        >
          <Avatar sx={{ m: 1, bgcolor: "secondary.main" }}>
            <PaymentsIcon />
          </Avatar>
          <Typography component="h1" variant="h5">
            Add a new expense
          </Typography>
          <Box
            component="form"
            onSubmit={handleSubmit}
            noValidate
            sx={{ mt: 1 }}
          >
            <Box
                sx={{ mt: 2 }}
              >
              <FormControl fullWidth>
                <InputLabel id="category-label" required>
                  Category
                </InputLabel>
                <Select
                  labelId="category-label"
                  value={category}
                  onChange={(e) => {
                    setCategory(e.target.value);
                  }}
                  id="category-select"
                  label="Category"
                >
                  {CATEGORIES.map((cat) => {
                    return (
                      <MenuItem value={cat}>{cat}</MenuItem>
                    );
                  })}
                </Select>
              </FormControl>
            </Box>
            <Box
            sx={{ mt: 2 }}
            >
              <FormControl fullWidth>
                    <InputLabel id="currency-select-label" required>
                      Currency
                    </InputLabel>
                    <Select
                      labelId="currency-select-label"
                      value={currency}
                      onChange={(e) => {
                        setCurrency(e.target.value);
                      }}
                      id="currency-select"
                      label="Currency"
                    >
                      {CURRENCY_LIST.map((curr) => {
                        return (
                          <MenuItem value={curr.code}>{curr.name}</MenuItem>
                        );
                      })}
                    </Select>
                  </FormControl>
            </Box>

            <TextField
              margin="normal"
              required
              fullWidth
              name="amount"
              label="Amount"
              type="number"
              id="amount"
              autoComplete="current-password"
            />
            <TextField
              margin="normal"
              fullWidth
              name="description"
              label="Description"
              id="password"
              autoComplete="current-password"
            />
            <Box
            sx={{ mt: 2 }}
            >
              <FormControl fullWidth>
                    <DatePicker 
                    value={date}
                    onChange={(newDate) => setDate(newDate)}
                    label="Date"/>
                  </FormControl>
            </Box>
            
            <Button
              type="submit"
              fullWidth
              variant="contained"
              sx={{ mt: 3, mb: 2 }}
            >
              Add
            </Button>
            <Grid container></Grid>
          </Box>
        </Box>
        <Copyright sx={{ mt: 8, mb: 4 }} />
      </Container>
    </React.Fragment>
  );
}
