import React from 'react';
import { Box, Typography } from '@mui/material';
import { blue } from '@mui/material/colors';

const primary = blue[500]; // #f44336

export default function Error() {
  return (
    <Box
      sx={{
        display: 'flex',
        justifyContent: 'center',
        flexDirection: 'column',
        alignItems: 'center',
        minHeight: '100vh',
        backgroundColor: primary,
      }}
    >
      <Typography variant="h1" style={{ color: 'white', fontWeight: 500 }}>
        404
      </Typography>
      <Typography variant="h4" style={{ color: 'white', fontWeight: 500, textAlign: 'center' }}>
        Not found as well as the meaning of your life
      </Typography>
    </Box>
  );
}