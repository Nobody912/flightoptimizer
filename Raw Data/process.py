import csv
import json
import sys

# Output storage format
# {
#     "AIRPORTCODE": {
#         "code": "AIRPORTCODE",
#         "state": "STATE",
#         "validDestinations": {
#             "AIRPORTCODE" : PRICE_INT
#             "FOO" : 999,
#             "BAR" : 998,
#             "BAZ" : 997
#         }
#     }
# }

with open("T_DB1B_MARKET.csv") as csvfile:
    with open("output.json", "w") as jsonfile:
        counter = 0
        reader = csv.DictReader(csvfile)
        output = {}
        for row in reader:
            counter += 1
            percentComplete = (counter / 2097153) * 100

            print(percentComplete, sep=' ', end='\n', file=sys.stdout, flush=True)

            if (float(row["MARKET_FARE"]) > 6.00):
                if row["ORIGIN"] not in output:
                    output[row["ORIGIN"]] = {
                        "code": row["ORIGIN"],
                        "state": row["ORIGIN_STATE_ABR"],
                        "validDestinations": {}
                    }
            
                elif row["DEST"] not in output[row["ORIGIN"]]["validDestinations"]:
                    output[row["ORIGIN"]]["validDestinations"][row["DEST"]] = [float(row["MARKET_FARE"])]
                
                else:
                    output[row["ORIGIN"]]["validDestinations"][row["DEST"]].append(float(row["MARKET_FARE"]))

        for origin in output:
            for destination in output[origin]["validDestinations"]:
                sum = 0;
                counter = 0;
                for num in output[origin]["validDestinations"][destination]:
                    sum += float(num);
                    counter += 1;

                output[origin]["validDestinations"][destination] = int(sum / counter);


        json.dump(output, jsonfile, indent=4)