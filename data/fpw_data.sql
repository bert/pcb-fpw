-- phpMyAdmin SQL Dump
-- version 3.2.0.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jan 23, 2010 at 11:07 AM
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
  `warning` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`footprint_id`),
  UNIQUE KEY `FootprintID` (`footprint_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=25 ;

--
-- Dumping data for table `fpw_data`
--

INSERT INTO `fpw_data` (`footprint_id`, `footprint_type`, `footprint_name`, `footprint_units`, `footprint_status`, `package_body_length`, `package_body_width`, `package_body_height`, `package_is_radial`, `number_of_pins`, `number_of_columns`, `number_of_rows`, `pin1_location`, `pitch_x`, `pitch_y`, `count_x`, `count_y`, `pin_pad_exceptions_string`, `number_of_exceptions`, `pin_drill_diameter`, `pad_diameter`, `pad_length`, `pad_width`, `pad_shapes_type`, `pin1_square`, `pad_solder_mask_clearance`, `pad_clearance`, `silkscreen_package_outline`, `silkscreen_indicate_1`, `silkscreen_length`, `silkscreen_width`, `silkscreen_line_width`, `courtyard`, `courtyard_length`, `courtyard_width`, `courtyard_line_width`, `courtyard_clearance_with_package`, `thermal`, `thermal_nopaste`, `thermal_length`, `thermal_width`, `thermal_solder_mask_clearance`, `thermal_clearance`, `fiducial`, `fiducial_pad_diameter`, `fiducial_pad_solder_mask_clearance`, `fiducial_clearance`, `c1`, `g1`, `z1`, `c2`, `g2`, `z2`, `remarks`, `warning`) VALUES
(1, 'BGA', 'BGA100C100P10X10_1100X1100X140', 'mm', 'EXPERIMENTAL', 11, 11, 1.4, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', ''),
(2, 'BGA', 'BGA100C100P10X10_1100X1100X170', 'mm', 'EXPERIMENTAL', 11, 11, 1.7, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO-192AAC-1', ''),
(3, 'BGA', 'BGA100C100P10X10_1100X1100X170A', 'mm', 'EXPERIMENTAL', 11, 11, 1.7, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 1, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', ''),
(4, 'BGA', 'BGA100C100P10X10_1100X1100X200', 'mm', 'EXPERIMENTAL', 11, 11, 2, 0, 100, 10, 10, 'UPPER_LEFT', 1, 1, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', ''),
(5, 'BGA', 'BGA100C50P10X10_600X600X110', 'mm', 'EXPERIMENTAL', 6, 6, 1.1, 0, 100, 10, 10, 'UPPER_LEFT', 0.5, 0.5, 0, 0, '', 0, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 6, 6, 0.2, 1, 8, 8, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO-195', ''),
(6, 'BGA', 'BGA100C50P11X11_600X600X100', 'mm', 'EXPERIMENTAL', 6, 6, 1, 0, 100, 11, 11, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'A1,A6,A11,D5,D6,D7,E4,E8,F1,F4,F6,F8,F11,G4,G8,H5,H6,H7,L1,L6,L11', 21, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 6, 6, 0.2, 1, 8, 8, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO-225', ''),
(7, 'BGA', 'BGA100C50P14X14_800X800X120', 'mm', 'EXPERIMENTAL', 8, 8, 1.2, 0, 100, 14, 14, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'C3,C4,C5,C6,C7,C9,C10,C11,C12,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,G4,G5,G6,G7,G8,G9,G10,G11,G12,H3,H4,H5,H6,H7,H8,H9,H10,H11,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,M3,M4,M5,M6,M8,M9,M10,M11,M12', 96, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 8, 8, 0.2, 1, 10, 10, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(8, 'BGA', 'BGA100C50P14X14_800X800X135', 'mm', 'EXPERIMENTAL', 8, 8, 1.35, 0, 100, 14, 14, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'C4,C5,C6,C7,C8,C9,C10,C11,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,M4,M5,M6,M7,M8,M9,M10,M11', 96, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 8, 8, 0.2, 1, 10, 10, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(9, 'BGA', 'BGA100C50P15X15_1000X1000X120', 'mm', 'EXPERIMENTAL', 10, 10, 1.2, 0, 100, 15, 15, 'UPPER_LEFT', 0.5, 0.5, 0, 0, 'B2,B14,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,P2,P14,', 125, 0, 0.25, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 10, 10, 0.2, 1, 12, 12, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(10, 'BGA', 'BGA100C65P10X10_800X800X140', 'mm', 'EXPERIMENTAL', 8, 8, 1.4, 0, 100, 10, 10, 'UPPER_LEFT', 0.65, 0.65, 0, 0, '', 0, 0, 0.35, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 8, 8, 0.2, 1, 10, 10, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(11, 'BGA', 'BGA100C80P10X10_1000X1000X140', 'mm', 'EXPERIMENTAL', 10, 10, 1.4, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 10, 10, 0.2, 1, 12, 12, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(12, 'BGA', 'BGA100C80P10X10_1000X1000X150', 'mm', 'EXPERIMENTAL', 10, 10, 1.5, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 10, 10, 0.2, 1, 12, 12, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(13, 'BGA', 'BGA100C80P10X10_900X900X100', 'mm', 'EXPERIMENTAL', 9, 9, 1, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.35, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(14, 'BGA', 'BGA100C80P10X10_900X900X120', 'mm', 'EXPERIMENTAL', 9, 9, 1.2, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(15, 'BGA', 'BGA100C80P10X10_900X900X120A', 'mm', 'EXPERIMENTAL', 9, 9, 1.2, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO216', ''),
(16, 'BGA', 'BGA100C80P10X10_900X900X140', 'mm', 'EXPERIMENTAL', 9, 9, 1.4, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO-205AB', ''),
(17, 'BGA', 'BGA100C80P10X10_900X900X150', 'mm', 'EXPERIMENTAL', 9, 9, 1.5, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(18, 'BGA', 'BGA100C80P10X10_900X900X160', 'mm', 'EXPERIMENTAL', 9, 9, 1.6, 0, 100, 10, 10, 'UPPER_LEFT', 0.8, 0.8, 0, 0, '', 0, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 9, 9, 0.2, 1, 11, 11, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MS-205', ''),
(19, 'BGA', 'BGA100C80P11X11_1100X1100X140', 'mm', 'EXPERIMENTAL', 11, 11, 1.4, 0, 100, 11, 11, 'UPPER_LEFT', 0.8, 0.8, 0, 0, 'D5,D6,D7,E4,E5,E6,E7,E8,F4,F5,F6,F7,F8,G4,G5,G6,G7,G8,H5,H6,H7', 21, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 11, 11, 0.2, 1, 13, 13, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, '', ''),
(20, 'BGA', 'BGA100C80P12X12_1000X1000X140', 'mm', 'EXPERIMENTAL', 10, 10, 1.4, 0, 100, 12, 12, 'UPPER_LEFT', 0.8, 0.8, 0, 0, 'C3,C4,C5,C6,C7,C8,C9,C10,D3,D10,E3,E3,E5,E6,E7,E8,E10,F3,F5,F6,F7,F8,F10,G3,G5,E6,G7,G8,G10,H3,H5,H6,H7,H8,H10,J3,J10,K3,K4,K5,K6,K7,K8,K9,K10', 44, 0, 0.4, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 10, 10, 0.2, 1, 12, 12, 0.05, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MO-205AC', ''),
(21, 'BGA', 'BGA1020C100P32X32_3300X3300X350', 'mm', 'EXPERIMENTAL', 33, 33, 3.5, 0, 1020, 32, 32, 'UPPER_LEFT', 1, 1, 0, 0, 'A1,A32,AM1,AM32', 4, 0, 0.5, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 33, 33, 0.2, 1, 37, 37, 0.05, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'package is also known as JEDEC MS-034AAP-1', ''),
(22, 'BGA', 'BGA1023C100P32X32_3300X3300X272', 'mm', 'EXPERIMENTAL', 33, 33, 2.72, 0, 1023, 32, 32, 'UPPER_LEFT', 1, 1, 0, 0, 'A1', 1, 0, 0.5, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 33, 33, 0.2, 1, 37, 37, 0.05, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', ''),
(23, 'BGA', 'BGA1023C100P32X32_3300X3300X287', 'mm', 'EXPERIMENTAL', 33, 33, 2.87, 0, 1023, 32, 32, 'UPPER_LEFT', 1, 1, 0, 0, 'A1', 1, 0, 0.45, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 33, 33, 0.2, 1, 35, 35, 0.05, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', ''),
(24, 'BGA', 'BGA1036C100P44X44_4500X4500X275', 'mm', 'EXPERIMENTAL', 45, 45, 2.75, 0, 1036, 44, 44, 'UPPER_LEFT', 1, 1, 0, 0, 'H8,H9,H10,H11,H12,H13,H14,H15,H16,H17,H18,H19,H20,H21,H22,H23,H24,H25,H26,H27,H28,H29,H30,H31,H32,H33,H34,H35,H36,H37,J8,J9,J10,J11,J12,J13,J14,J15,J16,J17,J18,J19,J20,J21,J22,J23,J24,J25,J26,J27,J28,J29,J30,J31,J32,J33,J34,J35,J36,J37,K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,K35,K36,K37,L8,L9,L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,L31,L32,L33,L34,L35,L36,L37,M8,M9,M10,M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,M31,M32,M33,M34,M35,M36,M37,N8,N9,N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,N31,N32,N33,N34,N35,N36,N37,P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31,P32,P33,P34,P35,P36,P37,R8,R9,R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,R31,R32,R33,R34,R35,R36,R37,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,U8,U9,U10,U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,U21,U22,U23,U24,U25,U26,U27,U28,U29,U30,U31,U32,U33,U34,U35,U36,U37,V8,V9,V10,V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,V21,V22,V23,V24,V25,V26,V27,V28,V29,V30,V31,V32,V33,V34,V35,V36,V37,W8,W9,W10,W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,W21,W22,W23,W24,W25,W26,W27,W28,W29,W30,W31,W32,W33,W34,W35,W36,W37,Y8,Y9,Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21,Y22,Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,Y31,Y32,Y33,Y34,Y35,Y36,Y37,AA8,AA9,AA10,AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,AA21,AA22,AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,AA31,AA32,AA33,AA34,AA35,AA36,AA37,AB8,AB9,AB10,AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,AB21,AB22,AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,AB31,AB32,AB33,AB34,AB35,AB36,AB37,AC8,AC9,AC10,AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,AC21,AC22,AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,AC31,AC32,AC33,AC34,AC35,AC36,AC37,AD8,AD9,AD10,AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,AD21,AD22,AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,AD31,AD32,AD33,AD34,AD35,AD36,AD37,AE8,AE9,AE10,AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,AE31,AE32,AE33,AE34,AE35,AE36,AE37,AF8,AF9,AF10,AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,AF31,AF32,AF33,AF34,AF35,AF36,AF37,AG8,AG9,AG10,AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,AG31,AG32,AG33,AG34,AG35,AG36,AG37,AH8,AH9,AH10,AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,AH31,AH32,AH33,AH34,AH35,AH36,AH37,AJ8,AJ9,AJ10,AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,AJ31,AJ32,AJ33,AJ34,AJ35,AJ36,AJ37,AK8,AK9,AK10,AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,AK31,AK32,AK33,AK34,AK35,AK36,AK37,AL8,AL9,AL10,AL11,AL12,AL13,AL14,AL15,AL16,AL17,AL18,AL19,AL20,AL21,AL22,AL23,AL24,AL25,AL26,AL27,AL28,AL29,AL30,AL31,AL32,AL33,AL34,AL35,AL36,AL37,AM8,AM9,AM10,AM11,AM12,AM13,AM14,AM15,AM16,AM17,AM18,AM19,AM20,AM21,AM22,AM23,AM24,AM25,AM26,AM27,AM28,AM29,AM30,AM31,AM32,AM33,AM34,AM35,AM36,AM37,AN8,AN9,AN10,AN11,AN12,AN13,AN14,AN15,AN16,AN17,AN18,AN19,AN20,AN21,AN22,AN23,AN24,AN25,AN26,AN27,AN28,AN29,AN30,AN31,AN32,AN33,AN34,AN35,AN36,AN37,AP8,AP9,AP10,AP11,AP12,AP13,AP14,AP15,AP16,AP17,AP18,AP19,AP20,AP21,AP22,AP23,AP24,AP25,AP26,AP27,AP28,AP29,AP30,AP31,AP32,AP33,AP34,AP35,AP36,AP37,AR8,AR9,AR10,AR11,AR12,AR13,AR14,AR15,AR16,AR17,AR18,AR19,AR20,AR21,AR22,AR23,AR24,AR25,AR26,AR27,AR28,AR29,AR30,AR31,AR32,AR33,AR34,AR35,AR36,AR37,AT8,AT9,AT10,AT11,AT12,AT13,AT14,AT15,AT16,AT17,AT18,AT19,AT20,AT21,AT22,AT23,AT24,AT25,AT26,AT27,AT28,AT29,AT30,AT31,AT32,AT33,AT34,AT35,AT36,AT37,AU8,AU9,AU10,AU11,AU12,AU13,AU14,AU15,AU16,AU17,AU18,AU19,AU20,AU21,AU22,AU23,AU24,AU25,AU26,AU27,AU28,AU29,AU30,AU31,AU32,AU33,AU34,AU35,AU36,AU37', 900, 0, 0.55, 0, 0, 'ROUND', 0, 0, 0, 1, 1, 45, 45, 0.2, 1, 49, 49, 0.05, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '');
