import * as React from 'react';
import Link from '@mui/material/Link';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Title from './Title';

// Generate Order Data
function createData(id, category, date, amount, currency, description) {
  return { id, category, date, description, currency, amount };
}

const rows = [
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
  createData(
    64,
    "Food",
    "2023-05-03 14:23:43",
    120,
    "UAH",
    "Carrefour"
  ),
];

function preventDefault(event) {
  event.preventDefault();
}

export default function Orders() {
  return (
    <React.Fragment>
      <Title>Recent Expenses</Title>
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
          {rows.map((row) => (
            <TableRow key={row.id}>
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
