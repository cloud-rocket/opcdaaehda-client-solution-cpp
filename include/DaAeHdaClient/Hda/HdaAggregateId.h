/*
 * Copyright (c) 2011-2021 Technosoftware GmbH. All rights reserved
 * Web: https://www.technosoftware.com
 *
 * The source code in this file is covered under a dual-license scenario:
 *   - Owner of a purchased license: SCLA 1.0
 *   - GPL V3: everybody else
 *
 * SCLA license terms accompanied with this source code.
 * See SCLA 1.0: https://technosoftware.com/license/Source_Code_License_Agreement.pdf
 *
 * GNU General Public License as published by the Free Software Foundation;
 * version 3 of the License are accompanied with this source code.
 * See https://technosoftware.com/license/GPLv3License.txt
 *
 * This source code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef TECHNOSOFTWARE_HDAAGGREGATEID_H
#define TECHNOSOFTWARE_HDAAGGREGATEID_H

namespace Technosoftware
{
	namespace DaAeHdaClient
	{
		/**
		 * @enum	HdaAggregateId
		 *
		 * @brief	Defines constants for well-known item aggregates. This indicates the aggregate to be
		 * 			used when retrieving processed history. The precise meaning of each aggregate may be
		 * 			server specific. Aggregates not supported by the server shall return E_INVALIDARG in
		 * 			the error code for that aggregate. Additional aggregates may be defined by vendors.
		 * 			Server specific aggregates must be defined with values beginning at 0x80000000. The
		 * 			OPC foundation reserves all aggregates IDs from 0 to 0x7fffffff.
		 *
		 * @ingroup  HDAClient
		 */

		enum class HdaAggregateId {

			/**
 			 * @brief    Do not retrieve an aggregate.
 			 */
			NoAggregate = 0,

			/**
			 * @brief    Do not retrieve an aggregate. This is used for retrieving interpolated values.
			 */
			Interpolative = 1,

			/**
			 * @brief    Retrieve the totalized value (time integral) of the data over the resample interval.
			 */
			Total = 2,

			/**
			 * @brief    Retrieve the average data over the resample interval.
			 */
			Average = 3,

			/**
			 * @brief    Retrieve the time weighted average data over the resample interval.
			 */
			TimeAverage = 4,

			/**
			 * @brief    Retrieve the number of raw values over the resample interval.
			 */
			Count = 5,

			/**
			 * @brief    Retrieve the standard deviation over the resample interval.
			 */
			StandardDeviation = 6,

			/**
			 * @brief    Retrieve the minimum value in the resample interval and the timestamp of the minimum value.
			 */
			MinimumActualTime = 7,

			/**
			 * @brief    Rrieve the minimum value in the resample interval.
			 */
			Minimum = 8,

			/**
			 * @brief    Retrieve the maximum value in the resample interval and the timestamp of the maximum value.
			 */
			MaximumActualTime = 9,

			/**
			 * @brief    Retrieve the maximum value in the resample interval.
			 */
			Maximum = 10,

			/**
			 * @brief    Retrieve the value at the beginning of the resample interval. The time stamp is the time stamp of the beginning of the interval.
			 */
			Start = 11,

			/**
			 * @brief    Retrieve the value at the end of the resample interval. The time stamp is the time stamp of the end of the interval. 
			 */
			End = 12,

			/**
			 * @brief    Retrieve the difference between the first and last value in the resample interval.
			 */
			Delta = 13,

			/**
			 * @brief    Retrieve the slope of the regression line over the resample interval.
			 */
			RegSlope = 14,

			/**
			 * @brief    Retrieve the intercept of the regression line over the resample interval. This is the value of the regression line at the start of the interval.
			 */
			RegConst = 15,

			/**
			 * @brief    Retrieve the standard deviation of the regression line over the resample interval.
			 */
			RegDev = 16,

			/**
			 * @brief    Retrieve the variance over the sample interval.
			 */
			Variance = 17,

			/**
			 * @brief    Retrieve the difference between the minimum and maximum value over the sample interval.
			 */
			Range = 18,

			/**
			 * @brief    Retrieve the duration (in seconds) of time in the interval during which the data is good.
			 */
			DurationGood = 19,

			/**
			 * @brief    Retrieve the duration (in seconds) of time in the interval during which the data is bad.
			 */
			DurationBad = 20,

			/**
			 * @brief    Retrieve the percent of data (1 equals 100 percent) in the interval which has good quality.
			 */
			PercentGood = 21,

			/**
			 * @brief    Retrieve the percent of data (1 equals 100 percent) in the interval which has bad quality.
			 */
			PercentBad = 22,

			/**
			 * @brief    Retrieve the worst quality of data in the interval.
			 */
			WorstQuality = 23,

			/**
			 * @brief    Retrieve the number of annotations in the interval.
			 */
			Annotations = 24
		};
	}
}

#endif // TECHNOSOFTWARE_HDAAGGREGATEID_H