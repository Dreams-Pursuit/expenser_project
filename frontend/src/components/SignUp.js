import * as React from "react";
import Avatar from "@mui/material/Avatar";
import Button from "@mui/material/Button";
import CssBaseline from "@mui/material/CssBaseline";
import TextField from "@mui/material/TextField";
import FormControlLabel from "@mui/material/FormControlLabel";
import Checkbox from "@mui/material/Checkbox";
import Link from "@mui/material/Link";
import Grid from "@mui/material/Grid";
import Box from "@mui/material/Box";
import InputLabel from "@mui/material/InputLabel";
import Select from "@mui/material/Select";
import MenuItem from "@mui/material/MenuItem";
import FormControl from "@mui/material/FormControl";
import LockOutlinedIcon from "@mui/icons-material/LockOutlined";
import Typography from "@mui/material/Typography";
import Container from "@mui/material/Container";

import Copyright from "./Copyright";

import CURRENCY_LIST from "../data/currencyList";
import useAxiosPrivate from "../hooks/useAxiosPrivate";
import axios from "../api/axios";

const SING_UP_PATH = "/auth/register";

export default function SignUp() {
  const [currency, setCurrency] = React.useState("UAH");
  const [success, setSuccess] = React.useState(false); // in development


  const handleSubmit = async (event) => {
    event.preventDefault();
    const formedData = new FormData(event.currentTarget);
    console.log(event.currentTarget);
    const data = {
      "email": formedData.get("email"),
      "password": formedData.get("password"),
      "main_currency": formedData.get("main-currency-select"),
    };
    console.log(data);

    try {
      const response = await axios.post(SING_UP_PATH, data, {
        headers: {
        "Content-Type": "text/plain"
      }});
      setSuccess(true);
      
    } catch (err) {
      console.log(err.response.data); //Handle required
      alert(err.response.data);
      
    }
  };

  return (
    <>
      {success ? (
        <Container component="main" maxWidth="xs">
          <CssBaseline />
          <Box
            sx={{
              marginTop: 8,
              display: "flex",
              flexDirection: "column",
              alignItems: "center",
            }}
          ></Box>
          <Typography component="h1" variant="h5">
              The sign up was successful
          </Typography>
          <Typography component="h4" variant="p">
              <Link href="/login" variant="body2">
                  Sign in
              </Link>
          </Typography>

        </Container>
      ) : (
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
              <LockOutlinedIcon />
            </Avatar>
            <Typography component="h1" variant="h5">
              Sign up
            </Typography>
            <Box
              component="form"
              noValidate
              onSubmit={handleSubmit}
              sx={{ mt: 3 }}
            >
              <Grid container spacing={2}>
              
                <Grid item xs={12}>
                  <TextField
                    required
                    fullWidth
                    id="email"
                    label="Email Address"
                    name="email"
                    autoComplete="email"
                  />
                </Grid>
                <Grid item xs={12}>
                  <TextField
                    required
                    fullWidth
                    name="password"
                    label="Password"
                    type="password"
                    id="password"
                    autoComplete="new-password"
                  />
                </Grid>
                <Grid item xs={12}>
                  <FormControl fullWidth>
                    <InputLabel id="main-currency-select-label">
                      Main Currency
                    </InputLabel>
                    <Select
                      labelId="main-currency-select-label"
                      value={currency}
                      onChange={(e) => {
                        setCurrency(e.target.value);
                      }}
                      id="main-currency-select"
                      name="main-currency-select"
                      label="Main Currency"
                    >
                      {CURRENCY_LIST.map((curr) => {
                        return (
                          <MenuItem value={curr.code}>{curr.name}</MenuItem>
                        );
                      })}
                    </Select>
                  </FormControl>
                </Grid>
                <Grid item xs={12}>
                  <FormControlLabel
                    control={
                      <Checkbox value="allowExtraEmails" color="primary" />
                    }
                    label="I want to receive inspiration via email."
                  />
                </Grid>
              </Grid>
              <Button
                type="submit"
                fullWidth
                variant="contained"
                sx={{ mt: 3, mb: 2 }}
              >
                Sign Up
              </Button>
              <Grid container justifyContent="flex-end">
                <Grid item>
                  <Link href="/login" variant="body2">
                    Already have an account? Sign in
                  </Link>
                </Grid>
              </Grid>
            </Box>
          </Box>
          <Copyright sx={{ mt: 5 }} />
        </Container>
      )}
    </>
  );
}
