import * as React from 'react';
import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Paper from '@mui/material/Paper';
import Copyright from '../../Copyright';
import AuthedLayout from '../AuthedLayout';

import TansactionsTable from './TansactionsTable';

export default function FormGenerator() {
    return (
        <AuthedLayout>

            <Container maxWidth="lg" sx={{ mt: 10, mb: 4 }}>
                <Grid container spacing={3}>
                    {/* Reports */}
                    <Grid item xs={12}>
                        <Paper sx={{ p: 2, display: 'flex', flexDirection: 'column' }}>
                            <TansactionsTable />
                        </Paper>
                    </Grid>
                </Grid> 
                <Copyright sx={{ pt: 4 }} />
            </Container>
        </AuthedLayout>
    )
}