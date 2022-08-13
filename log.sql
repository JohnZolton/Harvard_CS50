-- Keep a log of any SQL queries you execute as you solve the mystery.
--Your goal is to identify:
    --Who the thief is,
    --What city the thief escaped to, and
    --Who the thief’s accomplice is who helped them escape
--start:
--the theft took place on July 28, 2021 and that it took place on Humphrey Street.
Select *
FROM crime_scene_reports
WHERE
    (day = 28 and year = 2021 and month = 7);
--result: interviews conducted with 3 witnesses; theft took place at 10:15 am
-- at the humphrey st bakery

Select *
FROM interviews
WHERE
    (year = 2021 and day = 28 and month =7);
--result: look at parking lot and drive way 10:15-10:25
--theif was at ATM on Leggett Street that monring
--theif said on phone planning to take earliest flight out tomorrow

Select *
FROM bakery_security_logs
WHERE
    (year = 2021 and day = 28 and month = 7 and
     hour =10 and minute > 14 and minute <25);
-- returns 8 license plates

Select *
FROM people
WHERE license_plate in (
    Select license_plate
    FROM bakery_security_logs
    WHERE
        (year = 2021 and day = 28 and month = 7 and
        hour =10 and minute > 14 and minute <25)
);
--returns names, phone and passport numbers

--want phone calls from above's phone numbers
--want flights from above's passport numbers
--want earliest flight out the next day

SELECT id
FROM airports
WHERE city like '%fiftyville%';
--fiftyville's id = 8

SELECT *
FROM flights
WHERE (
    year = 2021 and
    day = 29 and
    month = 7 and
    origin_airport_id = 8
);
--returns 5 flights, earliest 8:20, flight id = 36, destination id = 4

SELECT full_name, city
FROM airports
WHERE id = 4;
--destination is NYC

SELECT seat
FROM passengers
WHERE passport_number in (
    Select passport_number
    FROM people
    WHERE license_plate in (
        Select license_plate
        FROM bakery_security_logs
        WHERE
            (year = 2021 and day = 28 and month = 7 and
            hour =10 and minute > 14 and minute <25)
))
and flight_id = 36;
-- returns 4 seats : 3B, 4A, 6C and 7B
-- time to investigate the ATM on Leggett st


SELECT *
FROM atm_transactions
WHERE (
    year = 2021 and day = 28 and month = 7 and atm_location = 'Leggett Street'
);
--returns account numbers, types and amounts

SELECT person_id
FROM bank_accounts
WHERE account_number in (
    SELECT account_number
    FROM atm_transactions
    WHERE (
        year = 2021 and day = 28 and month = 7 and atm_location = 'Leggett Street'
));
--returns 9 person ID's

SELECT * from phone_calls
WHERE (
    year = 2021 and day = 28 and month = 7
);
--returns a bunch of phone numbers, remembered interview said the phone call was <1minute

SELECT * from phone_calls
WHERE (
    year = 2021 and day = 28 and month = 7 and duration <60
);
--returns 9 calls

--getting ID of the 9 callers
SELECT id
FROM people
WHERE phone_number in (
    SELECT caller from phone_calls
    WHERE (
    year = 2021 and day = 28 and month = 7 and duration <60
)
);

-- so far we have pools for phone, license plate, and passport numbers
--combining

-- people table has phone number, passport number, and license plate


SELECT id
FROM people
WHERE phone_number in (
    -- query for phone number:
    SELECT caller from phone_calls
    WHERE (
    year = 2021 and day = 28 and month = 7 and duration <60
    ))
and
--query for passport number:
    passport_number in (SELECT passport_number
    FROM passengers
    WHERE passport_number in (
        Select passport_number
        FROM people
        WHERE license_plate in (
            Select license_plate
            FROM bakery_security_logs
            WHERE
                (year = 2021 and day = 28 and month = 7 and
                hour =10 and minute > 14 and minute <25)
    ))
    and flight_id = 36)
--query for license plates
and
    license_plate in
    (Select license_plate
    FROM bakery_security_logs
    WHERE
        (year = 2021 and day = 28 and month = 7 and
        hour =10 and minute > 14 and minute <25))
and
    id in
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number in (
        SELECT account_number
        FROM atm_transactions
        WHERE (
            year = 2021 and day = 28 and month = 7 and atm_location = 'Leggett Street'
    )))
;
-- yields one result! BRUCE id: 686048

--find who bruce called
SELECT name
from people
where phone_number = (
SELECT receiver
from phone_calls
WHERE (
caller in (
    SELECT phone_number
    from people
    where id = 686048
)
and year = 2021 and day = 28 and month = 7 and duration <60));
--accomplice is Robin!