import * as React from 'react';
import Link from '@mui/material/Link';
import Typography from '@mui/material/Typography';
import Title from './Title';
import useAxiosPrivate from '../../hooks/useAxiosPrivate';

function preventDefault(event) {
  event.preventDefault();
}

export default function Deposits() {

  const [highlight, setHighlight] = React.useState({});
  const axiosPrivate = useAxiosPrivate();


  React.useEffect(() => {
    let isMounted = true;
    const controller = new AbortController();

    function formData(response) {
      const slicedData = response.slice(response.length - 8, response.length - 1);

      let maxIndex = 0;
      slicedData.forEach((element, index) => {
        if (element.amount > slicedData[maxIndex].amount) {
          maxIndex = index;
        }
      });
      setHighlight(slicedData[maxIndex])
      // console.log("Sliced data");
      // console.log(slicedData);
      // setHighlight(Math.max(...slicedData));

    }

    const getTransactions = async () => {
      console.log("in getTran Charts");

      try {
        const response = await axiosPrivate.post('/user/transactions', {
          signal: controller.signal
        });
        console.log("The request was completed. Deposits");
        console.log(response);
        isMounted && formData(response.data);
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
      <Title>Highlights</Title>
      <Typography component="p" variant="h4">
        {highlight.currency}{highlight.amount}
      </Typography>
      <Typography color="text.secondary" sx={{ flex: 1 }}>
        {highlight.category} <br/>
        on {highlight.date}
      </Typography>
      <div>
        <Link color="primary" href="/reports" onClick={preventDefault}>
          Your recent largest purchase.
        </Link>
      </div>
    </React.Fragment>
  );
}
