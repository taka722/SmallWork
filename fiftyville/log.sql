-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Looking for crime reports on Humphrey Street on July 28, 2021
-- Looking for the report of the stolen duck on Humphrey Street on July 28, 2021
SELECT *
FROM crime_scene_reports
WHERE year = 2021
AND month = 07
AND day = 28
AND street = 'Humphrey Street';


-- Examining the report's description for clues
SELECT description
FROM crime_scene_reports
WHERE year = 2021
AND month = 07
AND day = 28
AND street = 'Humphrey Street';


-- Finding unique witnesses from interviews who might have seen something on Humphrey Street on July 28, 2021
SELECT DISTINCT interviews.name, interviews.transcript
FROM interviews
JOIN crime_scene_reports ON interviews.year = crime_scene_reports.year
    AND interviews.month = crime_scene_reports.month
    AND interviews.day = crime_scene_reports.day
    AND crime_scene_reports.street = 'Humphrey Street'
WHERE crime_scene_reports.month = 07
AND crime_scene_reports.day = 28
AND crime_scene_reports.year = 2021;


-- ATM Transactions on Leggett Street:
-- Eugene mentioned seeing someone he recognized withdrawing money from an ATM on Leggett Street earlier in the morning before the theft.
-- Find ATM transactions on Leggett Street on the morning of July 28, 2021
-- Find all ATM transactions on Leggett Street on July 28, 2021
-- theves withdraw the money according to the witness.
SELECT *
FROM atm_transactions
WHERE day = 28
AND month = 7
AND year = 2021
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- try to identify who withdraw the money at leggett street.


-- Flight Information:
-- Raymond overheard the thief planning to take the earliest flight out of Fiftyville the
-- next day and asking someone on the phone to purchase a ticket.

-- Find the earliest flight out of Fiftyville on July 29, 2021
SELECT flights.*
FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.day = 29
AND flights.month = 7
AND flights.year = 2021
ORDER BY flights.hour ASC, flights.minute ASC
LIMIT 1;



-- Phone Call Records:
-- Raymond also heard the thief on a phone call, so you might check the phone_calls table for calls made around the time the thief left the bakery.
-- Check for phone calls made around the time the thief left the bakery
SELECT *
FROM phone_calls
WHERE day = 28
AND month = 7
AND year = 2021
AND duration < 60;



-- Identify Potential Suspects from ATM Transactions:
-- Cross-reference the atm_transactions with people based on the license plate or other identifiers to find out who withdrew money at Leggett Street on the morning of July 28, 2021.



-- 1: Identifying people based on vehicles seen in the bakery's parking lot
SELECT people.*
FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
AND bakery_security_logs.year = 2021;





-- 2: Matching ATM withdrawals with people's bank accounts
SELECT people.*
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.year = 2021
AND atm_transactions.transaction_type = 'withdraw';


-- 3: Identify Passengers on the Earliest Flight:
SELECT people.*
FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE passengers.flight_id = 36;





-- 4: Finding people who made short calls on the day of the theft
SELECT people.*
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.day = 28
AND phone_calls.month = 7
AND phone_calls.year = 2021
AND phone_calls.duration < 60;




-- Here is the SQL query you can use to find out the destination city for flight ID 36:
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
);
-- new yourk



-- combine the result of 1, 2, 3, 4. It will show the thief
SELECT DISTINCT p.*
FROM people p
JOIN (
    SELECT DISTINCT people.id
    FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.day = 28
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.year = 2021
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute
    BETWEEN 15
    AND 25
    AND bakery_security_logs.activity = 'exit'

) AS bakery_people ON p.id = bakery_people.id
JOIN (
    SELECT DISTINCT people.id
    FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021
    AND atm_transactions.transaction_type = 'withdraw'
) AS atm_people ON p.id = atm_people.id
JOIN (
    SELECT DISTINCT people.id
    FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    WHERE passengers.flight_id = 36
) AS flight_people ON p.id = flight_people.id
JOIN (
    SELECT DISTINCT people.id
    FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_calls.day = 28
    AND phone_calls.month = 7
    AND phone_calls.year = 2021
    AND phone_calls.duration < 60
) AS phone_people ON p.id = phone_people.id;


-- Bruce is thief
-- Robin is supporter




SELECT
    pc.id AS call_id,
    caller.name AS caller_name,
    caller.phone_number AS caller_phone,
    receiver.name AS receiver_name,
    receiver.phone_number AS receiver_phone,
    pc.duration
FROM
    phone_calls pc
JOIN
    people caller ON pc.caller = caller.phone_number
JOIN
    people receiver ON pc.receiver = receiver.phone_number
WHERE
    pc.day = 28 AND
    pc.month = 7 AND
    pc.year = 2021 AND
    pc.duration < 60;

-- Finding the destination of the first flight ticket for the day after the theft.
SELECT city
FROM airports
WHERE id = (SELECT destination_airport_id
            FROM flights
            WHERE day = "29"
            AND month = "7"
            AND year = "2021"
            ORDER BY hour,minute LIMIT 1);

SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = "28"
AND month = "7"
AND year = "2021"
AND duration < "60"
AND caller = (SELECT phone_number
              FROM people
              WHERE name = "Bruce");





