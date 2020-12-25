-- Keep a log of any SQL queries you execute as you solve the mystery.

-- viewed all the tables
.tables


--view schema of 
.schema crime_scene_reports

--see the description of the crime
SELECT id, description FROM crime_scene_reports WHERE month=7 AND day=28 AND street = "Chamberlin Street";


--view schema of interviews
.schema interviews

--view the interviews
SELECT id, transcript, name FROM interviews WHERE month=7 AND day=28;


--view the schema of courthouse_loogs
.schema courthouse_security_logs

--view the information about vehicles int the mentioned timeframe
SELECT id, license_plate, hour, minute, activity FROM courthouse_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute < 25;


--view schema of atm_transactions
.schema atm_transactions

--view the transactions
SELECT id, account_number, amount, transaction_type FROM atm_transactions WHERE month=7 AND day=28 AND atm_location="Fifer Street";


--view
.schema phone_calls

--get the info avour phone calls
SELECT id, caller, receiver, duration FROM phone_calls WHERE month=7 AND day=28 AND duration < 60;



--For Culprit
SELECT id, name FROM people WHERE 
license_plate IN
        (SELECT license_plate FROM courthouse_security_logs WHERE
        month=7 AND day=28 AND hour=10 AND minute < 25 AND activity="exit")
AND
phone_number IN
        (SELECT caller FROM phone_calls WHERE
        month=7 AND day=28 AND duration < 60)
AND
id IN
        (SELECT person_id FROM bank_accounts WHERE
        account_number IN
                (SELECT account_number FROM atm_transactions WHERE
                month=7 AND day=28 AND atm_location="Fifer Street" AND transaction_type="withdraw"))
AND
passport_number IN
        (SELECT passport_number FROM passengers WHERE
        flight_id IN
                (SELECT id FROM flights WHERE
                origin_airport_id IN
                        (SELECT id FROM airports WHERE
                        city="Fiftyville") AND month=7 AND day=29 ORDER BY(hour) LIMIT 1));


--For the city he escaped to
SELECT city FROM airports WHERE
id IN
        (SELECT destination_airport_id FROM flights WHERE
        month=7 AND day=29 ORDER BY(hour) LIMIT 1);


--For his helper
SELECT name FROM people WHERE
phone_number IN
        (SELECT receiver FROM phone_calls WHERE
        month=7 AND day=28 AND duration<60 AND caller IN
                (SELECT phone_number FROM people WHERE name="Ernest"));
