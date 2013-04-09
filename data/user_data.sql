-- phpMyAdmin SQL Dump
-- version 3.2.0.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 23, 2010 at 06:41 AM
-- Server version: 5.1.36
-- PHP Version: 5.3.0

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `pcb_fpw`
--

-- --------------------------------------------------------

--
-- Table structure for table `user_data`
--

CREATE TABLE IF NOT EXISTS `user_data` (
  `footprint_id` int(11) NOT NULL AUTO_INCREMENT,
  `footprint_type` enum('NO_TYPE','BGA','CAPA','CAPC','RES') COLLATE utf8_bin NOT NULL,
  `footprint_name` text COLLATE utf8_bin NOT NULL,
  `footprint_units` enum('NO_UNITS','mil','mil/100','mm') COLLATE utf8_bin NOT NULL,
  `footprint_status` enum('NO_STATUS','EXPERIMENTAL','PRIVATE','PUBLIC','STABLE') COLLATE utf8_bin NOT NULL,
  `package_body_length` double NOT NULL,
  `package_body_width` double NOT NULL,
  `package_body_height` double NOT NULL,
  `package_is_radial` tinyint(1) NOT NULL,
  `number_of_pins` int(11) NOT NULL,
  `number_of_columns` int(11) NOT NULL,
  `number_of_rows` int(11) NOT NULL,
  `pin1_location` enum('NO_LOCATION','UPPER_LEFT','MIDDLE_LEFT','LOWER_LEFT','UPPER_MIDDLE','MIDDLE_MIDDLE','LOWER_MIDDLE','UPPER_RIGHT','MIDDLE_RIGHT','LOWER_RIGHT','LEFT_TOP','RIGHT_TOP','LEFT_BOTTOM','RIGHT_BOTTOM') COLLATE utf8_bin NOT NULL,
  `pitch_x` double NOT NULL,
  `pitch_y` double NOT NULL,
  `count_x` int(11) NOT NULL,
  `count_y` int(11) NOT NULL,
  `pin_pad_exceptions_string` text COLLATE utf8_bin NOT NULL,
  `number_of_exceptions` int(11) NOT NULL,
  `pin_drill_diameter` double NOT NULL,
  `pad_diameter` double NOT NULL,
  `pad_length` double NOT NULL,
  `pad_width` double NOT NULL,
  `pad_shapes_type` enum('NO_SHAPE','ROUND','SQUARE','OCTAGONAL','ROUND_ELONGATED') COLLATE utf8_bin NOT NULL,
  `pin1_square` tinyint(1) NOT NULL,
  `pad_solder_mask_clearance` double NOT NULL,
  `pad_clearance` double NOT NULL,
  `silkscreen_package_outline` tinyint(1) NOT NULL,
  `silkscreen_indicate_1` tinyint(1) NOT NULL,
  `silkscreen_length` double NOT NULL,
  `silkscreen_width` double NOT NULL,
  `silkscreen_line_width` double NOT NULL,
  `courtyard` tinyint(1) NOT NULL,
  `courtyard_length` double NOT NULL,
  `courtyard_width` double NOT NULL,
  `courtyard_line_width` double NOT NULL,
  `courtyard_clearance_with_package` double NOT NULL,
  `thermal` tinyint(1) NOT NULL,
  `thermal_nopaste` tinyint(1) NOT NULL,
  `thermal_length` double NOT NULL,
  `thermal_width` double NOT NULL,
  `thermal_solder_mask_clearance` double NOT NULL,
  `thermal_clearance` double NOT NULL,
  `fiducial` tinyint(1) NOT NULL,
  `fiducial_pad_diameter` double NOT NULL,
  `fiducial_pad_solder_mask_clearance` double NOT NULL,
  `fiducial_clearance` double NOT NULL,
  `c1` double NOT NULL,
  `g1` double NOT NULL,
  `z1` double NOT NULL,
  `c2` double NOT NULL,
  `g2` double NOT NULL,
  `z2` double NOT NULL,
  `remarks` text COLLATE utf8_bin NOT NULL,
  `warning` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`footprint_id`),
  UNIQUE KEY `FootprintID` (`footprint_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=2 ;

--
-- Dumping data for table `user_data`
--

INSERT INTO `user_data` (`footprint_id`, `footprint_type`, `footprint_name`, `footprint_units`, `footprint_status`, `package_body_length`, `package_body_width`, `package_body_height`, `package_is_radial`, `number_of_pins`, `number_of_columns`, `number_of_rows`, `pin1_location`, `pitch_x`, `pitch_y`, `count_x`, `count_y`, `pin_pad_exceptions_string`, `number_of_exceptions`, `pin_drill_diameter`, `pad_diameter`, `pad_length`, `pad_width`, `pad_shapes_type`, `pin1_square`, `pad_solder_mask_clearance`, `pad_clearance`, `silkscreen_package_outline`, `silkscreen_indicate_1`, `silkscreen_length`, `silkscreen_width`, `silkscreen_line_width`, `courtyard`, `courtyard_length`, `courtyard_width`, `courtyard_line_width`, `courtyard_clearance_with_package`, `thermal`, `thermal_nopaste`, `thermal_length`, `thermal_width`, `thermal_solder_mask_clearance`, `thermal_clearance`, `fiducial`, `fiducial_pad_diameter`, `fiducial_pad_solder_mask_clearance`, `fiducial_clearance`, `c1`, `g1`, `z1`, `c2`, `g2`, `z2`, `remarks`, `warning`) VALUES
(1, 'NO_TYPE', '', 'NO_UNITS', 'NO_STATUS', 0, 0, 0, 0, 0, 0, 0, 'NO_LOCATION', 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 'NO_SHAPE', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '');