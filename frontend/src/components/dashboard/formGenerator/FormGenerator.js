import * as React from 'react';
import Container from '@mui/material/Container';
import Grid from '@mui/material/Grid';
import Paper from '@mui/material/Paper';
import Chart from '../Chart';
import Deposits from '../Deposits';
import Orders from '../Orders';
import Copyright from '../../Copyright';
import AuthedLayout from '../AuthedLayout';
import Button from '@mui/material/Button';
import GenerateLink from './GenerateLink';

export default function FormGenerator() {
    return (
        <AuthedLayout title={"Form Generator"}>
            <Container maxWidth="lg" sx={{ mt: 10, mb: 4 }}>
                <Grid container spacing={3}>
                    {/* Generate Link */}
                    <Grid item xs={12}>
                        <Paper sx={{ p: 2, display: 'flex', flexDirection: 'column' }}>
                            <GenerateLink />
                        </Paper>
                    </Grid>
                </Grid>
                <Copyright sx={{ pt: 4 }} />
            </Container>
        </AuthedLayout>
    )
}