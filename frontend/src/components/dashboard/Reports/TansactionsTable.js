import * as React from 'react';
import { DataGrid } from '@mui/x-data-grid';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import Divider from '@mui/material/Divider';
import Box from "@mui/material/Box"
import Title from '../Title';
import { axiosPrivate } from '../../../api/axios';

const columns = [
    { field: 'id',
     headerName: 'ID',
     minWidth: 90,
     flex: 0.2,
    },
    {
      field: 'category',
      headerName: 'Category',
      minWidth: 150,
      flex: 0.2,
    },
    {
      field: 'amount',
      headerName: 'Amount',
      type: 'number',
      minWidth: 100,
      flex: 0.2,
    },
    {
      field: 'Currency',
      headerName: 'Currency',
      minWidth: 100,
      flex: 0.2,
    },
    {
      field: 'date',
      headerName: 'Date',
      // description: 'This column has a value getter and is not sortable.',
      // sortable: false,
      minWidth: 150,
      flex: 0.2,
      // valueGetter: (params) =>
      //   `${params.row.firstName || ''} ${params.row.lastName || ''}`,
    },
  ];
  



export default function TansactionsTable() {
    const [rows, setRows] = React.useState([
      { id: 1, lastName: 'Snow', firstName: 'Jon', age: 35 },
      { id: 2, lastName: 'Lannister', firstName: 'Cersei', age: 42 },
      { id: 3, lastName: 'Lannister', firstName: 'Jaime', age: 45 },
      { id: 4, lastName: 'Stark', firstName: 'Arya', age: 16 },
      { id: 5, lastName: 'Targaryen', firstName: 'Daenerys', age: null },
      { id: 6, lastName: 'Melisandre', firstName: null, age: 150 },
      { id: 7, lastName: 'Clifford', firstName: 'Ferrara', age: 44 },
      { id: 8, lastName: 'Frances', firstName: 'Rossini', age: 36 },
      { id: 9, lastName: 'Roxie', firstName: 'Harvey', age: 65 },
    ]);

    React.useEffect(() => {
      async function fecthLatestTransactions() {
        let response = {};
        try {
          response = await axiosPrivate.get('/');
          // response = await response.json();
        } catch (err) {
          alert(err);
        }
        console.log(response)
      }

      fecthLatestTransactions()
    })
    return (
        <React.Fragment>
            <Title>All Transactions</Title>
            <Box sx={{ mt: 2 }}>
                <DataGrid
                    rows={rows}
                    columns={columns}
                    
                    initialState={{
                    pagination: {
                        paginationModel: {
                        pageSize: 50,
                        },
                    },
                    }}
                    pageSizeOptions={[50]}
                    disableRowSelectionOnClick
                />
            </Box>
            
        </React.Fragment>
    )
}