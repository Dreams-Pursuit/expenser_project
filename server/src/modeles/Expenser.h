// generated by ddl2cpp.txt ../dbc.sql /Users/andrey/Desktop/Expenser Project/expenser_project/server/src Expenser
#ifndef EXPENSER_SRC_H
#define EXPENSER_SRC_H

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

namespace Expenser
{
  namespace AccountData_
  {
    struct USERID
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "USER_ID";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T USERID;
            T& operator()() { return USERID; }
            const T& operator()() const { return USERID; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
    };
    struct EMAIL
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "EMAIL";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T EMAIL;
            T& operator()() { return EMAIL; }
            const T& operator()() const { return EMAIL; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
    struct PASSWORD
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "PASSWORD";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T PASSWORD;
            T& operator()() { return PASSWORD; }
            const T& operator()() const { return PASSWORD; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
    struct MainCurrency
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "main_currency";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T mainCurrency;
            T& operator()() { return mainCurrency; }
            const T& operator()() const { return mainCurrency; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
  } // namespace AccountData_

  struct AccountData: sqlpp::table_t<AccountData,
               AccountData_::USERID,
               AccountData_::EMAIL,
               AccountData_::PASSWORD,
               AccountData_::MainCurrency>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "account_data";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T accountData;
        T& operator()() { return accountData; }
        const T& operator()() const { return accountData; }
      };
    };
  };
  namespace TransactionsList_
  {
    struct USERID
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "USER_ID";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T USERID;
            T& operator()() { return USERID; }
            const T& operator()() const { return USERID; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::require_insert>;
    };
    struct TRANSACTIONID
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "TRANSACTION_ID";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T TRANSACTIONID;
            T& operator()() { return TRANSACTIONID; }
            const T& operator()() const { return TRANSACTIONID; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
    };
    struct CATEGORY
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "CATEGORY";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T CATEGORY;
            T& operator()() { return CATEGORY; }
            const T& operator()() const { return CATEGORY; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
    struct AMOUNT
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "AMOUNT";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T AMOUNT;
            T& operator()() { return AMOUNT; }
            const T& operator()() const { return AMOUNT; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::floating_point, sqlpp::tag::require_insert>;
    };
    struct CURRENCY
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "CURRENCY";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T CURRENCY;
            T& operator()() { return CURRENCY; }
            const T& operator()() const { return CURRENCY; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
    struct DATE
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "DATE";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T DATE;
            T& operator()() { return DATE; }
            const T& operator()() const { return DATE; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::require_insert>;
    };
    struct DESCRIPTION
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "DESCRIPTION";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T DESCRIPTION;
            T& operator()() { return DESCRIPTION; }
            const T& operator()() const { return DESCRIPTION; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::text, sqlpp::tag::can_be_null>;
    };
    struct BALANCEAFTER
    {
      struct _alias_t
      {
        static constexpr const char _literal[] =  "BALANCE_AFTER";
        using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
        template<typename T>
        struct _member_t
          {
            T BALANCEAFTER;
            T& operator()() { return BALANCEAFTER; }
            const T& operator()() const { return BALANCEAFTER; }
          };
      };
      using _traits = sqlpp::make_traits<sqlpp::floating_point, sqlpp::tag::can_be_null>;
    };
  } // namespace TransactionsList_

  struct TransactionsList: sqlpp::table_t<TransactionsList,
               TransactionsList_::USERID,
               TransactionsList_::TRANSACTIONID,
               TransactionsList_::CATEGORY,
               TransactionsList_::AMOUNT,
               TransactionsList_::CURRENCY,
               TransactionsList_::DATE,
               TransactionsList_::DESCRIPTION,
               TransactionsList_::BALANCEAFTER>
  {
    struct _alias_t
    {
      static constexpr const char _literal[] =  "transactions_list";
      using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
      template<typename T>
      struct _member_t
      {
        T transactionsList;
        T& operator()() { return transactionsList; }
        const T& operator()() const { return transactionsList; }
      };
    };
  };
} // namespace Expenser
#endif
