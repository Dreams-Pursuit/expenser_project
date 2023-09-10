import * as React from 'react';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import Divider from '@mui/material/Divider';
import Box from "@mui/material/Box"
import Title from '../Title';
import { axiosPrivate } from '../../../api/axios';

export default function GenerateLink() {
    const [generatedLink, setGeneratedLink] = React.useState("");

    function handleGenerate(e) {
        e.preventDefault();
        setGeneratedLink("https://expenser.com")
        // onClick={() => {navigator.clipboard.writeText(generatedLink)}}
    }

    function handleCopy(e) {
        e.preventDefault();
        navigator.clipboard.writeText(generatedLink).then(
            () => {
                alert("The link was copied to the clipboard: " + generatedLink);
            }
        );
    }

    return (
        <React.Fragment>
            <Title>Generator</Title>
            <Typography component="p" variant="p">
                Generate a new link to access your form and fill out the expenses without any need to login. At least for 30 days...
            </Typography>
            <Divider sx={{ my: 1 }} />
            <Box sx={{ display: 'flex', flexDirection: 'row', justifyContent: 'space-between' }}>
                <Typography component="p" variant="p">
                    {generatedLink}
                </Typography>
                <Button variant="contained" disabled={generatedLink ? false : true} onClick={handleCopy}>Copy Link</Button>
            </Box>
            <Box sx={{ mt: 2 }}>
                <Button onClick={handleGenerate} variant="contained">Generate a new Link</Button>
            </Box>
        </React.Fragment>
    )
}