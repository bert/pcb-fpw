-- phpMyAdmin SQL Dump
-- version 3.2.0.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 21, 2010 at 07:15 AM
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
-- Table structure for table `fpw_data`
--

CREATE TABLE IF NOT EXISTS `fpw_data` (
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
  PRIMARY KEY (`footprint_id`),
  UNIQUE KEY `FootprintID` (`footprint_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=10 ;

--
-- Dumping data for table `fpw_data`
--

INSERT INTO `fpw_data` (`footprint_id`, `footprint_type`, `footprint_name`, `footprint_units`, `footprint_status`, `package_body_length`, `package_body_width`, `package_body_height`, `package_is_radial`, `number_of_pins`, `number_of_columns`, `number_of_rows`, `pin1_location`, `pitch_x`, `pitch_y`, `count_x`, `count_y`, `pin_pad_exceptions_string`, `number_of_exceptions`, `pin_drill_diameter`, `pad_diameter`, `pad_length`, `pad_width`, `pad_shapes_type`, `pin1_square`, `pad_solder_mask_clearance`, `pad_clearance`, `silkscreen_package_outline`, `silkscreen_indicate_1`, `silkscreen_length`, `silkscreen_width`, `silkscreen_line_width`, `courtyard`, `courtyard_length`, `courtyard_width`, `courtyard_line_width`, `courtyard_clearance_with_package`, `thermal`, `thermal_nopaste`, `thermal_length`, `thermal_width`, `thermal_solder_mask_clearance`, `thermal_clearance`, `fiducial`, `fiducial_pad_diameter`, `fiducial_pad_solder_mask_clearance`, `fiducial_clearance`, `c1`, `g1`, `z1`, `c2`, `g2`, `z2`, `remarks`) VALUES
(1, 'BGA', 'BGA100C100P10X10_1100X1100X140', 'mm', 'EXPERIMENTAL', 11, 11, 1.4, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(2, 'BGA', 'BGA100C100P10X10_1100X1100X170', 'mm', 'EXPERIMENTAL', 11, 11, 1.7, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'is also known as JEDEC MO-192AAC-1'),
(3, 'BGA', 'BGA100C100P10X10_1100X1100X170A', 'mm', 'EXPERIMENTAL', 11, 11, 1.7, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 1, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(4, 'BGA', 'BGA100C100P10X10_1100X1100X200', 'mm', 'EXPERIMENTAL', 11, 11, 2, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(5, 'BGA', 'BGA100C50P10X10_600X600X110', 'mm', 'EXPERIMENTAL', 6, 6, 1.1, 0, 100, 10, 10, 'UPPER_LEFT', 0.5, 0.5, 0, 0, '', 0, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 6, 6, 0.2, 1, 8, 8, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, ''),
(6, 'BGA', 'BGA100C50P11X11_600X600X100', 'mm', 'EXPERIMENTAL', 6, 6, 1, 0, 100, 11, 11, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'A1,A6,A11,D5,D6,D7,E4,E8,F1,F4,F6,F8,F11,G4,G8,H5,H6,H7,L1,L6,L11', 21, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 6, 6, 0.2, 1, 8, 8, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, ''),
(7, 'BGA', 'BGA100C50P14X14_800X800X120', 'mm', 'EXPERIMENTAL', 8, 8, 1.2, 0, 100, 14, 14, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'C3,C4,C5,C6,C7,C9,C10,C11,C12,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,G4,G5,G6,G7,G8,G9,G10,G11,G12,H3,H4,H5,H6,H7,H8,H9,H10,H11,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,M3,M4,M5,M6,M8,M9,M10,M11,M12', 96, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 8, 8, 0.2, 1, 10, 10, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, ''),
(8, 'BGA', 'BGA100C50P14X14_800X800X135', 'mm', 'EXPERIMENTAL', 8, 8, 1.35, 0, 100, 14, 14, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'C4,C5,C6,C7,C8,C9,C10,C11,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,M4,M5,M6,M7,M8,M9,M10,M11', 96, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 8, 8, 0.2, 1, 10, 10, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, ''),
(9, 'BGA', 'BGA100C50P15X15_1000X1000X120', 'mm', 'EXPERIMENTAL', 10, 10, 1.2, 0, 100, 15, 15, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'B2,B14,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,P2,P14,', 125, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 10, 10, 0.2, 1, 12, 12, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '');
