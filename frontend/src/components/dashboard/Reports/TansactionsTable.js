import * as React from 'react';
import { DataGrid } from '@mui/x-data-grid';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import Divider from '@mui/material/Divider';
import Box from "@mui/material/Box"
import Title from '../Title';
import useAxiosPrivate from '../../../hooks/useAxiosPrivate';

const columns = [
    { field: 'transaction_id',
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
      field: 'currency',
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
  

  function getRowId(row) {
    return row.transaction_id;
  }

export default function TansactionsTable() {
    
    const [rows, setRows] = React.useState([]);

    const axiosPrivate = useAxiosPrivate()

    React.useEffect(() => {
      let isMounted = true; 
      const controller = new AbortController();

      async function fecthLatestTransactions() {
        try {
          const response = await axiosPrivate.post('/user/transactions', {
            signal: controller.signal
          });
          console.log(response);
          isMounted && setRows(response.data);
        } catch (err) {
          alert(err);
        }
      }

      fecthLatestTransactions()

      return () => {
        isMounted = false;
        controller.abort();
      }

    }, []);
    return (
        <React.Fragment>
            <Title>All Transactions</Title>
            <Box sx={{ mt: 2 }}>
                <DataGrid
                    rows={rows}
                    columns={columns}
                    getRowId={getRowId}
                    
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