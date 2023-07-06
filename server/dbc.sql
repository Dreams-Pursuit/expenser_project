CREATE TABLE account_data
(
    "USER_ID" bigint NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 9223372036854775807 CACHE 1 ),
    "EMAIL" character varying(50) COLLATE pg_catalog."default" NOT NULL,
    "PASSWORD" character varying(50) COLLATE pg_catalog."default" NOT NULL,
    main_currency character(3) COLLATE pg_catalog."default",
    CONSTRAINT account_data_pkey PRIMARY KEY ("USER_ID")
)
CREATE TABLE transactions_list
(
    "USER_ID" bigint NOT NULL,
    "TRANSACTION_ID" bigint NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 9223372036854775807 CACHE 1 ),
    "CATEGORY" character varying(50) COLLATE pg_catalog."default" NOT NULL,
    "AMOUNT" numeric(8,2) NOT NULL,
    "CURRENCY" character(3) COLLATE pg_catalog."default" NOT NULL,
    "DATE" timestamp without time zone NOT NULL,
    "DESCRIPTION" character varying(150) COLLATE pg_catalog."default",
    CONSTRAINT transactions_list_pkey PRIMARY KEY ("TRANSACTION_ID"),
    CONSTRAINT user_id FOREIGN KEY ("USER_ID")
        REFERENCES public.account_data ("USER_ID") MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
)
COMMIT;