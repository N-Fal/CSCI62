# STEP 1: Import libraries
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# import sklearn as skl

# STEP 2: Read the training dataset into program
# 1. Use pandas to load the dataset into a padnas dataframe
dataFrame = pd.read_csv("clean_data.csv", delimiter = ",")
# 2. Print the first 5 rows of the dataframe along with the size of the dataframe.
print(dataFrame.head(5))
numRows, numColumns = dataFrame.shape
print(f"The data frame is {numRows} rows by {numColumns} columns")



# STEP 3: Data processing
# 1. Find the number of missing values in each column of your dataframe.
numMissing = dataFrame.isnull().sum()
# 2. Delete all the columns that have more than 35% of the values missing.
cleanedFrame = dataFrame.dropna(axis = 1, thresh = (0.65 * numRows))
dataFrame = cleanedFrame



# STEP 4: Visualization: Friends vs Followers count
# Use Matplotlib scatter plot to visualize friends_count vs followers_counts for both bots and nonbots. Include a legend in your plot.
# plt.scatter(dataFrame.friends_count, dataFrame.followers_count)
# plt.title("Friends vs. Followers")
# plt.xlabel("friends_count")
# plt.ylabel("followers_count")
# plt.show()

# STEP 5: Feature Engineering
bag_of_words = ["bot", "follow me", "free", "fake", "virus", "troll", "clone", "tweet me"]

# used to determine true/false for the binary coolumns
def binary(data):
    if data != "NaN":
        for sub in bag_of_words:
            if sub in str(data):
                return True
    return False

# use the 'apply' function to add the binary columns
dataFrame.insert(dataFrame.shape[1], "screen_name_binary", dataFrame.screen_name.apply(binary))
dataFrame.insert(dataFrame.shape[1], "name_binary", dataFrame.name.apply(binary))
dataFrame.insert(dataFrame.shape[1], "description_binary", dataFrame.description.apply(binary))
dataFrame.insert(dataFrame.shape[1], "status_binary", dataFrame.status.apply(binary))

print("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
print(dataFrame.head())

#STEP 6: Decision Tree Classifier