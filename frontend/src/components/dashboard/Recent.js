import * as React from 'react';
import Link from '@mui/material/Link';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Title from './Title';
import useAxiosPrivate from '../../hooks/useAxiosPrivate';
import { useNavigate } from 'react-router-dom';

// Generate Order Data
function createData(id, category, date, amount, currency, description) {
  return { id, category, date, description, currency, amount };
}



function preventDefault(event) {
  event.preventDefault();
}

export default function Recent() {
  const [transactions, setTransactions] = React.useState([]);

  const axiosPrivate = useAxiosPrivate();

  React.useEffect(() => {
    let isMounted = true;
    const controller = new AbortController();

    const getTransactions = async () => {
      console.log("in getTrans");

      try {
        const response = await axiosPrivate.post('/user/transactions', {
          signal: controller.signal
        });
        const lb = response.data.length - 8;
        const lowerBound = (lb < 0) ? 0 : lb;
        // console.log(response.data.slice(lowerBound , response.data.length));
        isMounted && setTransactions(response.data.slice(lowerBound , response.data.length));
      } catch (err) {

        console.log("Get transaction error");
        console.log(err);
      }
    }

    getTransactions();

    return () => {
      isMounted = false;
      controller.abort();
    }

  },[]);

  return (
    <React.Fragment>
      <Title>Recent</Title>
      <Table size="small">
        <TableHead>
          <TableRow>
            <TableCell>Date</TableCell>
            <TableCell>Category</TableCell>
            <TableCell>Description</TableCell>
            <TableCell align="right">Amount</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {transactions.map((row, index) => (
            <TableRow key={index}>
              <TableCell>{row.date}</TableCell>
              <TableCell>{row.category}</TableCell>
              <TableCell>{row.description}</TableCell>
              <TableCell align="right">{`${row.amount} ${row.currency} `}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
      <Link color="primary" href="#" onClick={preventDefault} sx={{ mt: 3 }}>
        See more orders
      </Link>
    </React.Fragment>
  );
}
