import * as React from 'react';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import Divider from '@mui/material/Divider';
import Box from "@mui/material/Box"
import Title from '../Title';

export default function GenerateLink() {

    return (
        <React.Fragment>
            <Title>Generator</Title>
            <Typography component="p" variant="p">
                Generate a new link to access your form and fill out the expenses without any need to login. At least for 30 days...
            </Typography>
            <Divider sx={{ my: 1 }} />
            <Box sx={{ display: 'flex', flexDirection: 'row', justifyContent: 'space-between' }}>
                <Typography component="p" variant="p">
                    {/* https:://expenser.com/sJGHGFUYFYcvutvTDytcYTFuyFYTcYYxRTxTRctyFytjF */}
                </Typography>
                <Button variant="contained" disabled>Copy Link</Button>
            </Box>
            <Box sx={{ mt: 2 }}>
                <Button variant="contained">Generate a new Link</Button>
            </Box>
        </React.Fragment>
    )
}