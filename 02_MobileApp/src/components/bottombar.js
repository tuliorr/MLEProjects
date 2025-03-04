// Imports
import React, { useState } from "react";
import { StyleSheet, View, Image, TouchableOpacity, Dimensions, } from "react-native";

// Ícones
import HomeInactive from "../../assets/homeInactive.png";
import SearchInactive from "../../assets/searchInactive.png";
import TicketInactive from "../../assets/ticketInactive.png";
import ProfileInactive from "../../assets/profileInactive.png";
import HomeActive from "../../assets/homeActive.png";
import SearchActive from "../../assets/searchActive.png";
import TicketActive from "../../assets/ticketActive.png";
import ProfileActive from "../../assets/profileActive.png";

// Constantes
const MAX_WIDTH = Dimensions.get("window").width;
const MAX_HEIGHT = Dimensions.get("window").height;

// Barra Inferior
export default function bottombar() {
    const [Home, setHome] = useState(HomeActive);
    const [Search, setSearch] = useState(SearchInactive);
    const [Ticket, setTicket] = useState(TicketInactive);
    const [Profile, setProfile] = useState(ProfileInactive);

    function handleHome() {
        if (Home === HomeActive) return;

        setHome(HomeActive);
        setSearch(SearchInactive);
        setTicket(TicketInactive);
        setProfile(ProfileInactive);
    }

    function handleSearch() {
        if (Search === SearchActive) return;

        setHome(HomeInactive);
        setSearch(SearchActive);
        setTicket(TicketInactive);
        setProfile(ProfileInactive);
    }

    function handleTicket() {
        if (Ticket === TicketActive) return;

        setHome(HomeInactive);
        setSearch(SearchInactive);
        setTicket(TicketActive);
        setProfile(ProfileInactive);
    }

    function handleProfile() {
        if (Profile === ProfileActive) return;

        setHome(HomeInactive);
        setSearch(SearchInactive);
        setTicket(TicketInactive);
        setProfile(ProfileActive);
    }

    return (
        <>
            <View style={styles.bar}>
                <View style={styles.buttons}>
                    <TouchableOpacity onPress={handleHome}>
                        <Image source={Home} style={styles.icons} />
                    </TouchableOpacity>
                    <TouchableOpacity onPress={handleSearch}>
                        <Image source={Search} style={styles.icons} />
                    </TouchableOpacity>
                    <TouchableOpacity onPress={handleTicket}>
                        <Image source={Ticket} style={styles.icons} />
                    </TouchableOpacity>
                    <TouchableOpacity onPress={handleProfile}>
                        <Image source={Profile} style={styles.icons} />
                    </TouchableOpacity>
                </View>
            </View>
        </>
    );
}

const styles = StyleSheet.create({
    bar: {
        position: "absolute",
        top: "92%",
        height: 90,
        width: MAX_WIDTH,
        backgroundColor: "#FFF",
    },
    buttons: {
        marginTop: "5%",
        marginLeft: "11%",
        width: "75%",
        flexDirection: "row",
        justifyContent: "space-between",
    },
    icons: {
        width: 30,
        height: 30,
    },
});
