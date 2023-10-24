import * as React from 'react';
import { useTheme } from '@mui/material/styles';
import { LineChart, Line, XAxis, YAxis, Label, ResponsiveContainer } from 'recharts';
import Title from './Title';
import useAxiosPrivate from '../../hooks/useAxiosPrivate';

// Generate Data
function createData(time, amount) {
  return { time, amount };
}


export default function Chart() {
  const [transactions, setTransactions] = React.useState([
    createData('00:00', 0),
    createData('03:00', 300),
    createData('06:00', 600),
    createData('09:00', 800),
    createData('12:00', 1500),
    createData('15:00', 2000),
    createData('18:00', 2400),
    createData('21:00', 2400),
    createData('24:00', undefined),
  ]);

  const theme = useTheme();
  const axiosPrivate = useAxiosPrivate();

  function formData(data) {
    console.log(data);
    const dataMap = new Map();

    // const dataArray = data.map((obj) => {
    //   return createData(obj.date.slice(0, 10), obj.amount);
    // });

    data.map((obj) => {
      const date = obj.date.slice(0, 10);
      if (dataMap.has(date)) {
        dataMap.set(date, dataMap.get(date) + obj.amount);
      } else {
        dataMap.set(date, obj.amount)
      }
    });
    let dataArray = []
    dataMap.forEach((value, key) => {
      // console.log()
      dataArray.push(createData(key, value));
    });
    // console.log("dataMap");
    // console.log(dataMap);

    // console.log("dataArray");
    // console.log(dataArray);
    setTransactions(dataArray);
  }

  React.useEffect(() => {
    let isMounted = true;
    const controller = new AbortController();

    const getTransactions = async () => {
      console.log("in getTran Charts");

      try {
        const response = await axiosPrivate.post('/user/transactions', {
          signal: controller.signal
        });
        console.log("The request was completed");
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
      <Title>Overview</Title>
      <ResponsiveContainer>
        <LineChart
          data={transactions}
          margin={{
            top: 16,
            right: 16,
            bottom: 0,
            left: 24,
          }}
        >
          <XAxis
            dataKey="time"
            stroke={theme.palette.text.secondary}
            style={theme.typography.body2}
          />
          <YAxis
            stroke={theme.palette.text.secondary}
            style={theme.typography.body2}
          >
            <Label
              angle={270}
              position="left"
              style={{
                textAnchor: 'middle',
                fill: theme.palette.text.primary,
                ...theme.typography.body1,
              }}
            >
              Expenses
            </Label>
          </YAxis>
          <Line
            isAnimationActive={false}
            type="monotone"
            dataKey="amount"
            stroke={theme.palette.primary.main}
            dot={false}
          />
        </LineChart>
      </ResponsiveContainer>
    </React.Fragment>
  );
}
