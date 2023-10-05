import { axiosPrivate } from "./axios";


export const getTransactions = async () => {
  console.log("in getTrans");

  try {
    const response = await axiosPrivate.post('/user/transactions', {
      signal: controller.signal
    });
    console.log(response);
    isMounted && setTransactions(response.data);
  } catch (err) {
    // navigate("/"); //Rewrite the authprovider to validate the session for the each page request
    console.log("Get transaction error");
    console.log(err);
  }
}